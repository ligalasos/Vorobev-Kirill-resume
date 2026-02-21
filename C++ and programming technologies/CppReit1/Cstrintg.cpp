#include <iostream>

// size_t Strlen(const char* str);. Вычисляет длину строки str (без учета нулевого символа).
size_t Strlen(const char* str) {
  int size = 0;
  while (str[size] != '\0') {
    ++size;
  }
  return size;
}

// int Strcmp(const char* first, const char* second);. Лексикографически сравнивает две строки.
// Если first < second, то возвращает произвольное отрицательное число, если first > second, то - положительное.
// В случае равенства возвращает 0.
int Strcmp(const char* first, const char* second) {
  int i = 0;
  while (first[i] != '\0' and second[i] != '\0') {
    if (first[i] > second[i]) {
      return 228;
    }
    if (second[i] > first[i]) {
      return -228;
    }
    ++i;
  }
  if (second[i] == '\0' and first[i] == '\0') {
    return 0;
  }
  if (second[i] == '\0') {
    return 228;
  }
  return -228;
}

// int Strncmp(const char* first, const char* second, size_t count);. То же, что и предыдущая функция,
// но сравнивает первые count символов строк (либо пока не встретит нулевой символ).
int Strncmp(const char* first, const char* second, size_t count) {
  size_t i = 0;
  while (i < count and first[i] != '\0' and second[i] != '\0') {
    if (first[i] > second[i]) {
      return 228;
    }
    if (second[i] > first[i]) {
      return -228;
    }
    ++i;
  }
  if (i == count or (first[i] == '\0' and second[i] == '\0')) {
    return 0;
  }
  if (first[i] == '\0') {
    return -228;
  }
  return 228;
}

// char* Strcpy(char* dest, const char* src);. Принимает строку src и копирует ее содержимое (вместе с нуль-терминатором) в dest. 
// Гарантируется, что dest указывает на область памяти, достаточную для хранения src. Возвращает dest.
// Замечание: формально, std::strcpy дополнительно требует, чтобы последовательности dest и src не перекрывались
// (то есть длина строки src должна быть больше расстояния между указателями), так как порядок копирования символов не определен.
// В этом задании допускается более слабое предположение: dest не указывает внутрь строки src.
char* Strcpy(char* dest, const char* src) {
  int i = 0;
  while (src[i] != '\0') {
    dest[i] = src[i];
    ++i;
  }
  dest[i] = '\0';
  return dest;
}

// char* Strncpy(char* dest, const char* src, size_t count);. То же, что и предыдущая функция,
// но копирует ровно count символов из src.
// Если count больше размера src, то оставшиеся символы заполняются нуль-символами. Возвращает dest.
char* Strncpy(char* dest, const char* src, size_t count) {
  if (count == 0) {
    return dest;
  }
  size_t counter = 0;
  while (src[counter] != '\0' && counter < count) {
    dest[counter] = src[counter];
    ++counter;
  }
  if (counter == count) {
    return dest;
  }
  while (counter <= count) {
    dest[counter] = '\0';
    ++counter;
  }
  return dest;
}

char *Strncpy(char *dest, const char *src, size_t count) {
  size_t i = 0;
  if (count == 0) {
    return dest;
  }
  while (src[i] != '\0' && i < count) {
    dest[i] = src[i];
    ++i;
  }
  while (i < count) {
    dest[i] = '\0';
    ++i;
  }

  return dest;
}


// char* Strcat(char* dest, const char* src);. Приписывает строку src в конец строки dest (конкатенация строк).
// Гарантируется, что dest указывает на область памяти, достаточную для хранения итоговой строки. Возвращает dest.
char* Strcat(char* dest, const char* src) {
  int i = 0;
  int j = 0;
  while (dest[i] != '\0') {
    ++i;
  }
  while (src[j] != '\0') {
    dest[i] = src[j];
    ++j;
    ++i;
  }
  dest[i] = '\0';
  return dest;
}

// char* Strncat(char* dest, const char* src, size_t count);. То же, что и предыдущая функция,
// но добавляет только первые count символов из src + нулевой символ.
// Если count больше чем длина src, то работает так же как и Strcat(dest, src). Возвращает dest.
char* Strncat(char* dest, const char* src, size_t count) {
  size_t i = 0;
  size_t j = 0;
  while (dest[i] != '\0') {
    ++i;
  }
  while (j < count and src[j] != '\0') {
    dest[i] = src[j];
    ++j;
    ++i;
  }
  dest[i] = '\0';
  return dest;
}

// const char* Strchr(const char* str, char symbol);.
// Возвращает указатель на первое появление символа symbol в строке str (с учетом нулевого символа), либо нулевой указатель,
// если такого символа нет.
// const char* Strchr(const char* str, char symbol) {
//   for (int i = 0; str[i] != '\0'; ++i) {
//     if (str[i] == symbol) {
//       return str + i;
//     }
//   }
//   return nullptr;
// }
const char *Strchr(const char *str, char symbol) {
  size_t i = 0;
  size_t len = Strlen(str);
  while (i <= len) {
    if (symbol == str[i]) {
      return str + i;
    }
    ++i;
  }
  return nullptr;
}


// const char* Strrchr(const char* str, char symbol);.
// Возвращает указатель на последнее появление символа symbol в строке str (с учетом нулевого символа),
// либо нулевой указатель, если такого символа нет.
const char* Strrchr(const char* str, char symbol) {
  int pointer = 0;
  for (int i = 0; str[i] != '\0'; ++i) {
    if (str[i] == symbol) {
      pointer = i;
    }
  }
  if (pointer) {
    return str + pointer;
  }
  return nullptr;
}

// size_t Strspn(const char* dest, const char* src);.
// Возвращает количество первых символов dest, которые встречаются в строке src (без учета нулевого символа).
// a b b b c d e
// a b b b c p k

size_t Find(const char* src, char value) {
  for (int i = 0; src[i] != '\0'; ++i) {
    if (src[i] == value) {
      return 1;
    }
  }
  return 0;
}

size_t Strspn(const char* dest, const char* src) {
  size_t sum = 0;
  for (int i = 0; dest[i] != '\0' and Find(src, dest[i]); ++i) {
    sum += 1;
  }
  return sum;
}

// size_t Strcspn(const char* dest, const char* src);.
// Возвращает количество первых символов dest, которые не встречаются в строке src (без учета нулевого символа).
size_t Strcspn(const char* dest, const char* src) {
  int sum = 0;
  for (int i = 0; dest[i] != '\0' and !Find(src, dest[i]); ++i) {
    sum += 1;
  }
  return sum;
}

// const char* Strpbrk(const char* dest, const char* breakset);.
// Возвращает указатель на первый элемент dest, который лежит в breakset,
// либо нулевой указатель, если такого элемента нет.
const char* Strpbrk(const char* dest, const char* breakset) {
  for (int i = 0; dest[i] != '\0'; ++i) {
    if (Find(breakset, dest[i])) {
      return dest + i;
    }
  }
  return nullptr;
}

// const char* Strstr(const char* str, const char* pattern);.
// Осуществляет поиск подстроки pattern в строке str. Возвращает указатель на начало
// первого вхождения, либо нулевой указатель, если вхождения найдено не было.
// const char* Strstr(const char* str, const char* pattern) {
//   if (pattern[0] == '\0') {
//     return str;
//   }
//   const char* i = str;
//   while (*i != '\0') {
//     bool is_under_str = true;
//     size_t j = 0;
//     while (pattern[j] != '\0') {
//       if (i[j] == '\0') {
//         return nullptr;
//       }
//       if (i[j] != pattern[j]) {
//         is_under_str = false;
//         break;
//       }
//       ++j;
//     }
//     if (is_under_str) {
//       return i;
//     }
//     ++i;
//   }
//   return nullptr;
// }

const char *Strstr(const char *str, const char *pattern) {
  size_t i = 0;
  size_t len = Strlen(str);
  size_t pat_len = Strlen(pattern);
  while (i < len) {
    size_t j = 0;
    bool flag = true;
    while (i + j < len && j < pat_len) {
      if (pattern[j] != str[i + j]) {
        flag = false;
      }
      ++j;
    }
    if (flag) {
      return str + i;
    }
    ++i;
  }
  return nullptr;
}


int main() {
  char* str = "tohellandback";
  std::cout << Strstr(str, "\0");


  return 0;
}