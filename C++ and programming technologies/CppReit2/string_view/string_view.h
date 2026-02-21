#ifndef STRING_VIEW_H
#define STRING_VIEW_H

#include <iostream>

class StringView {
  const char* str_ = nullptr;
  size_t size_ = 0;
 public:
  const char& Front() const;
  const char& Back() const;
  StringView(const char* str); // NOLINT
  explicit StringView(const char* str, size_t size);
  const char& operator[](size_t n) const;
  bool Empty() const;
  const char* Data() const;
  size_t Size() const;
  void RemovePrefix(size_t prefix_size);
  void RemoveSuffix(size_t suffix_size);
  StringView Substr(size_t pos, size_t count = -1);
  size_t Length() const;
  StringView() = default;
  void Swap(StringView& str);
};

#endif