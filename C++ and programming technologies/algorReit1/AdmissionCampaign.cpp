#include <iostream>

struct Abitur {
  int sum = 0;
  char fam[40];
  char name[40];
};

void MergeSort(Abitur* arr, int left, int right);

void MergeTwoArrays(Abitur* arr, int left, int mid, int right);

int main() {
  int n = 0;
  std::cin >> n;
  auto* arr = new Abitur[n];
  for (int i = 0; i < n; ++i) {
    int one = 0;
    int two = 0;
    int three = 0;
    std::cin >> arr[i].fam >> arr[i].name >> one >> two >> three;
    arr[i].sum = one + two + three;
  }
  MergeSort(arr, 0, n - 1);
  for (int i = 0; i < n; ++i) {
    std::cout << arr[i].fam << " " << arr[i].name << "\n";
  }
  delete[] arr;
  return 0;
}

void MergeSort(Abitur* arr, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    MergeSort(arr, left, mid);
    MergeSort(arr, mid + 1, right);
    MergeTwoArrays(arr, left, mid, right);
  }
}

void MergeTwoArrays(Abitur* arr, int left, int mid, int right) {
  int a_size = mid - left + 1;
  int b_size = right - mid;
  auto* a = new Abitur[a_size];
  auto* b = new Abitur[b_size];
  for (int i = 0; i < a_size; ++i) {
    a[i] = arr[left + i];
  }
  for (int i = 0; i < b_size; ++i) {
    b[i] = arr[mid + 1 + i];
  }
  int i = 0;
  int j = 0;
  int k = left;
  while (i < a_size && j < b_size) {
    if (a[i].sum > b[j].sum) {
      arr[k++] = a[i++];
    } else if (a[i].sum < b[j].sum) {
      arr[k++] = b[j++];
    } else {
      arr[k++] = a[i++];
    }
  }
  while (i < a_size) {
    arr[k++] = a[i++];
  }
  while (j < b_size) {
    arr[k++] = b[j++];
  }
  delete[] a;
  delete[] b;
}