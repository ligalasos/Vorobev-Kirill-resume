import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler, OrdinalEncoder
from pytorch_tabnet.multitask import TabNetMultiTaskClassifier
import torch.nn.functional as F
import torch
import warnings
warnings.filterwarnings('ignore')


class FocalLoss(torch.nn.Module):
    def __init__(self, gamma=2, alpha=0.75, reduction='mean'):
        super().__init__()
        self.gamma = gamma
        self.alpha = alpha
        self.reduction = reduction

    def forward(self, input, target):
        # input:  (batch_size, n_classes)  – логиты для одного таска (здесь n_classes=2)
        # target: (batch_size,)            – метки 0/1 для этого таска
        logits_pos = input[:, 1]            # логиты положительного класса
        prob_pos = torch.sigmoid(logits_pos)
        prob_neg = 1 - prob_pos

        target = target.float()
        pt = target * prob_pos + (1 - target) * prob_neg
        focal_weight = (1 - pt) ** self.gamma

        if self.alpha >= 0:
            alpha_t = self.alpha * target + (1 - self.alpha) * (1 - target)
            focal_weight = alpha_t * focal_weight

        loss = F.binary_cross_entropy(prob_pos, target, reduction='none') * focal_weight
        if self.reduction == 'mean':
            return loss.mean()
        else:
            return loss.sum()
        
# Параметры
RANDOM_STATE = 42
TEST_SIZE = 0.2
BATCH_SIZE = 512
VIRTUAL_BATCH_SIZE = 64
MAX_EPOCHS = 100
EARLY_STOPPING_ROUNDS = 20
PATIENCE = 15

# Загрузка данных
print("Загрузка тренировочных данных...")
train_main = pd.read_parquet('train_main_features.parquet')          # основные признаки
# train_extra = pd.read_parquet('train_extra_features.parquet')        # дополнительные признаки
train_targets = pd.read_parquet('train_target.parquet')    # целевые переменные

print("Загрузка тестовых данных...")
test_main = pd.read_parquet('test_main_features.parquet')
# test_extra = pd.read_parquet('test_extra_features.parquet')

# Объединение основных и дополнительных признаков по customer_id
# train = pd.merge(train_main, train_extra, on='customer_id', how='left')
# test = pd.merge(test_main, test_extra, on='customer_id', how='left')
train = train_main
test = test_main

# Целевые переменные
target_cols = [col for col in train_targets.columns if col != 'customer_id']
y_full = train_targets[target_cols].values  # shape (n_samples, 41)

# Удаляем customer_id из признаков
X_full = train.drop(columns=['customer_id'])
X_test = test.drop(columns=['customer_id'])

# Определяем типы признаков (по информации организаторов)
# В реальности нужно знать, какие столбцы категориальные.
# Поскольку названия обфусцированы, предположим, что все признаки с 'cat' в имени — категориальные.
cat_features = [col for col in X_full.columns if 'cat_feature' in col]
num_features = [col for col in X_full.columns if 'num_feature' in col]

# Обработка пропусков и кодирование категорий
print("Предобработка данных...")

# Для числовых признаков заполним медианой (по обучающей выборке)
num_median = X_full[num_features].median()
X_full[num_features] = X_full[num_features].fillna(num_median)
X_test[num_features] = X_test[num_features].fillna(num_median)

# Для категориальных применим OrdinalEncoder с обработкой неизвестных значений
# Важно: encoder должен быть обучен только на тренировочных данных
ordinal_enc = OrdinalEncoder(handle_unknown='use_encoded_value', unknown_value=-1)
# X_full_cat_encoded = ordinal_enc.fit_transform(X_full[cat_features])
# X_test_cat_encoded = ordinal_enc.transform(X_test[cat_features])

# Создаем DataFrame с закодированными категориями (имена столбцов сохраняем)
X_full_cat = pd.DataFrame(X_full[cat_features], columns=cat_features, index=X_full.index)
X_test_cat = pd.DataFrame(X_test[cat_features], columns=cat_features, index=X_test.index)

# Заменяем исходные категориальные столбцы на закодированные
X_full = X_full.drop(columns=cat_features).join(X_full_cat)
X_test = X_test.drop(columns=cat_features).join(X_test_cat)

# Теперь все признаки числовые. Масштабируем числовые признаки (включая закодированные категории)
scaler = StandardScaler()
X_full_scaled = scaler.fit_transform(X_full)
X_test_scaled = scaler.transform(X_test)

# Разделение на обучающую и валидационную выборки
X_train, X_valid, y_train, y_valid = train_test_split(
    X_full_scaled, y_full, test_size=TEST_SIZE, random_state=RANDOM_STATE, stratify=None  # stratify не подходит для multi-label
)
print(X_train.shape)
y_train = y_train[:, 19:21]
y_valid = y_valid[:, 19:21]
# Создание модели TabNetMultiTaskClassifier
# n_tasks = 41, n_classes=2 (бинарная классификация для каждого таргета)
model = TabNetMultiTaskClassifier(
    n_d=64,                 # размерность decision step
    n_a=64,                 # размерность attention step
    n_steps=5,              # количество шагов
    gamma=1.5,              # коэффициент дробления
    n_independent=2,        # количество независимых слоев в каждом шаге
    n_shared=2,             # количество общих слоев
    lambda_sparse=1e-4,     # разреженность
    optimizer_fn=torch.optim.Adam,
    optimizer_params=dict(lr=2e-2),
    mask_type='entmax',     # или 'sparsemax'
    scheduler_params=dict(mode='min', patience=5, min_lr=1e-5, factor=0.9),
    scheduler_fn=torch.optim.lr_scheduler.ReduceLROnPlateau,
    verbose=1,
    device_name='cuda' if torch.cuda.is_available() else 'cpu',
)

# Обучение
print("Обучение модели TabNet...")
model.fit(
    X_train=X_train, y_train=y_train,
    eval_set=[(X_valid, y_valid)],
    eval_name=['valid'],
    eval_metric=['auc'],            # метрика для мониторинга (ROC-AUC)
    max_epochs=MAX_EPOCHS,
    patience=PATIENCE,
    batch_size=BATCH_SIZE,
    virtual_batch_size=VIRTUAL_BATCH_SIZE,
    num_workers=4,
    drop_last=False,
    # loss_fn=torch.nn.functional.binary_cross_entropy_with_logits  # функция потерь для multi-label
    loss_fn=FocalLoss()
)

# Предсказание вероятностей для тестовой выборки
# predict_proba возвращает список массивов [n_samples, n_tasks, n_classes]
# Для вероятности положительного класса берем индекс 1
proba = model.predict_proba(X_test_scaled)  # форма (41, n_samples, 2) или (n_samples, 41, 2)? 
# В документации: для multitask возвращает список (n_tasks) массивов (n_samples, n_classes)
# Проверим и приведем к единому формату.
if isinstance(proba, list):
    # В версии 3.x predict_proba возвращает список длиной n_tasks
    # Каждый элемент: (n_samples, n_classes)
    # Соберем матрицу (n_samples, n_tasks) с вероятностью класса 1
    y_pred = np.column_stack([p[:, 1] for p in proba])
else:
    # Возможно, другая версия возвращает (n_samples, n_tasks, n_classes)
    y_pred = proba[:, :, 1]

# Формирование сабмита
submit = pd.DataFrame({
    'customer_id': test['customer_id'].values,
    **{f'predict_{i+1}_{j+1}': y_pred[:, i] for i, j in enumerate(range(41))}  # соответствие predict_1_1 ... predict_10_1
})

sample = pd.read_parquet('sample_submit.parquet')
pred_columns = [col for col in sample.columns if col != 'customer_id']
# Убедимся, что их 41
if len(pred_columns) != 41:
    raise ValueError("Количество столбцов предсказаний в sample_submit не равно 41")

# Создаем DataFrame с нужными именами
submit = pd.DataFrame({'customer_id': test['customer_id'].values})
for i, col_name in enumerate(pred_columns):
    submit[col_name] = y_pred[:, i]

# Сохраняем результат
submit.to_parquet('tabnet_submit.parquet', index=False)
print("Сабмит сохранён в tabnet_submit.parquet")