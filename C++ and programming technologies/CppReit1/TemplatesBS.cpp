#include <iostream>

template <class T>
T BinSearch(int* arr_two, int n, int m) {
  int left = 0;
  int right = m - 1;
  while (left <= right) {
    int middle = left + (right - left) / 2;
    if (arr_two[middle] < n) {
      left = middle + 1;
    } else if (n < arr_two[middle]) {
      right = middle - 1;
    } else {
      return true;
    }
  }
  return false;
}

template <class T, class U>
T LowerBound(int* arr_two, int n, int m) {
  int left = 0;
  int right = m - 1;
  while (left <= right) {
    int middle = left + (right - left) / 2;
    if (arr_two[middle] < n) {
      left = middle + 1;
    } else if (n < arr_two[middle]) {
      right = middle - 1;
    } else {
      return middle;
    }
  }
  if (left > 0) {
    return left;
  } else {
    std::cout << end;
    
  }
}

int main() {

  return 0;
}