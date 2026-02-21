#include <iostream>
#include <climits>

int Razmah(int* arr, int k, int n, int mid) {
  int i = 0;
  int count = 0;
  while (i + k - 1 < n) {
    if (arr[i + k - 1] - arr[i] <= mid) {
      count++;
      i += k;
    } else {
      i++;
    }
  }
  return count;
}

void Swap(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

int Partition(int* arr, int left, int right) {
  int pivot = arr[left + rand() % (right - left + 1)];
  int i = left;
  int j = right;
  while (true) {
    while (arr[i] < pivot) {
      ++i;
    }
    while (arr[j] > pivot) {
      --j;
    }
    if (i >= j) {
      break;
    }
    Swap(arr[i], arr[j]);
    ++i;
    --j;
  }
  return j;
}

void QuickSort(int* arr, int left, int right) {
  if (left >= right) {
    return;
  }
  int j = Partition(arr, left, right);
  QuickSort(arr, left, j);
  QuickSort(arr, j + 1, right);
}

int main() {
  int n = 0;
  int m = 0;
  int k = 0;
  std::cin >> n >> m >> k;
  int* arr = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  QuickSort(arr, 0, n - 1);
  int left = 0;
  int right = INT_MAX;
  while (left <= right) {
    int mid = (left + right) / 2;
    if (Razmah(arr, k, n, mid) >= m) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }
  std::cout << right;
  delete[] arr;
  return 0;
}