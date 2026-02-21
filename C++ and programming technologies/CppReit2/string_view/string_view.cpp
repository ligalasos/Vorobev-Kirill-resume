#include "string_view.h"
#include <iostream>

// Конструктора по умолчанию (nullptr строка).
// Конструктора от const char* (с подсчетом длины). Этот конструктор должен допускать неявные преобразования. Чтобы на это не ругался линтер, добавьте к строке с объявлением комментарий "// NOLINT".
// Конструктора от const char* и size_t (длина передается вторым параметром).
// Операции [].
// Методов Front() и Back(), которые возвращают первый и последний символ строки соответственно.
// Методов Size() и Length(), которые возвращают длину строки.
// Метод Empty() проверяет строку на пустоту.
// Метод Data() возвращает указатель на начало строки.
// Метода Swap(StringView&).
// Метода RemovePrefix(size_t prefix_size), который сдвигает начало строки на prefix_size.
// Метода RemoveSuffix(size_t suffix_size), который сдвигает конец строки на suffix_size.
// Метода Substr(size_t pos, size_t count = -1), который формирует из вызывающего объекта StringView на подстроку с началом pos и длины min(count, Size() - pos).

StringView::StringView(const char* str, size_t size) {
  this->str_ = str;
  this->size_ = size;
}

StringView::StringView(const char* str) { // NOLINT
  this->str_ = str;
  this->size_ = 0;
  while (str[this->size_] != '\0') {
    ++this->size_;
  }
}

const char& StringView::operator[](size_t n) const {
  return this->str_[n];
}

const char& StringView::Back() const{
  return str_[size_ - 1];
}


const char& StringView::Front() const {
  return this->str_[0];
}

size_t StringView::Size() const {
  return this->size_;
}

size_t StringView::Length() const {
  return this->size_;
}

bool StringView::Empty() const {
  return size_ == 0;
}

const char* StringView::Data() const {
  return this->str_;
}

void StringView::Swap(StringView& str) {
  std::swap(str_, str.str_);
  std::swap(size_, str.size_);
}

void StringView::RemovePrefix(size_t prefix_size) {
  this->str_ = this->str_ + prefix_size;
  this->size_ = this->size_ - prefix_size;
}

void StringView::RemoveSuffix(size_t suffix_size) {
  this->size_ = this->size_ - suffix_size;
}

StringView StringView::Substr(size_t pos, size_t count) {
  if (size_ - pos <= 0 and count <= 0) {
    return StringView{};
  }
  const char* new_str = this->str_ + pos;
  size_t new_size = std::min(count, this->size_ - pos);
  return StringView(new_str, new_size);
}
