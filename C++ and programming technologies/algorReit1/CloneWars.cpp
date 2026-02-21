//сдал
#include <iostream>

void QuickSort(int* arr, int left, int right);

int Partition(int* arr, int left, int right);

bool BinSearch(int* arr_two, int n, int m);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n = 0;
  std::cin >> n;
  int* arr_one = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> arr_one[i];
  }
  int m = 0;
  std::cin >> m;
  int* arr_two = new int[m];
  for (int i = 0; i < m; ++i) {
    std::cin >> arr_two[i];
  }
  //if (m > n) {
  QuickSort(arr_one, 0, n - 1);
  for (int i = 0; i < m; ++i) {
    if (!BinSearch(arr_one, arr_two[i], n)) {
      std::cout << "NO";
      delete[] arr_one;
      delete[] arr_two;
      return 0;
    }
  }
  std::cout << "YES";
  delete[] arr_one;
  delete[] arr_two;
  return 0;
  //}
  // QuickSort(arr_two, 0, m - 1);
  // for (int i = 0; i < n; ++i) {
  //   if (!BinSearch(arr_two, arr_one[i], m)) {
  //     std::cout << "NO";
  //     return 0;
  //   }
  // }
  // std::cout << "YES";
  // delete[] arr_one;
  // delete[] arr_two;
  // return 0;
}

void QuickSort(int* arr, int left, int right) {
  if (left >= right) {
    return;
  }
  int j = Partition(arr, left, right);
  QuickSort(arr, left, j);
  QuickSort(arr, j + 1, right);
}

int Partition(int* array, int left, int right) {
  int pivo = array[left + rand() % (right - left + 1)];
  int i = left;
  int j = right;
  while (true) {
    while (array[i] < pivo) {
      ++i;
    }
    while (array[j] > pivo) {
      --j;
    }
    if (i >= j) {
      break;
    }
    std::swap(array[i], array[j]);
    ++i;
    --j;
  }
  return j;
}

bool BinSearch(int* arr_two, int n, int m) {
  int left = 0;
  int right = m - 1;
  while (left <= right) {
    int middle = left + (right - left) / 2;
    if (n > arr_two[middle]) {
      left = middle + 1;
    } else if (n < arr_two[middle]) {
      right = middle - 1;
    } else {
      return true;
    }
  }
  return false;
}