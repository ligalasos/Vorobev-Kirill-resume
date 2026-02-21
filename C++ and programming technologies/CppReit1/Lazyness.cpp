#include <iostream>

int main() {
  int64_t k = 0;
  std::cin >> k;
  char arr[100000000];
  std::cin >> arr;
  int64_t j = 0;
  int64_t sum = 0;
  int64_t counter = 1;
  while (arr[j + k] != '\0') {
    if (arr[j] == arr[j + k]) {
      sum += counter;
      ++counter;
    } else {
      counter = 1;
    }
    ++j;
  }
  std::cout << sum;
  return 0;
}