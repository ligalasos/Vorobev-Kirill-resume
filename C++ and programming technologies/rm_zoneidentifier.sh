#!/bin/bash

# Директория для поиска (первый аргумент, по умолчанию текущая)
SEARCH_DIR="${1:-.}"

# Шаблон имени файла (регистронезависимый, можно изменить на нужный)
PATTERN="*zoneidentifier*"

# Проверка существования директории
if [ ! -d "$SEARCH_DIR" ]; then
    echo "Ошибка: директория '$SEARCH_DIR' не найдена."
    exit 1
fi

echo "Поиск файлов, соответствующих шаблону '$PATTERN' в '$SEARCH_DIR' ..."

# Сбор файлов в массив (с обработкой пробелов в именах)
files=()
while IFS= read -r -d '' file; do
    files+=("$file")
done < <(find "$SEARCH_DIR" -type f -iname "$PATTERN" -print0)

if [ ${#files[@]} -eq 0 ]; then
    echo "Файлы не найдены."
    exit 0
fi

echo "Найдено файлов: ${#files[@]}"
echo "Список файлов:"
printf '%s\n' "${files[@]}"

echo
read -p "Удалить эти файлы? (y/N): " confirm

if [[ "$confirm" =~ ^[YyДд]$ ]]; then
    rm -v "${files[@]}"
    echo "Удаление завершено."
else
    echo "Операция отменена."
fi