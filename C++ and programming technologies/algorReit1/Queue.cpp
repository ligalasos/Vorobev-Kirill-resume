#include <iostream>

void Swap(int* arr, int i, int parent) {
  int swap = arr[i];
  arr[i] = arr[parent];
  arr[parent] = swap;
}

int Parent(int i) {
  return (i - 1) / 2;
}

int LeftChild(int i) {
  return 2 * i + 1;
}

int RightChild(int i) {
  return 2 * i + 2;
}

int GetMax(int* arr) {
  return arr[0];
}

void SiftUp(int* arr, int i, int& current_two) {
  if (arr[i] <= arr[Parent(i)]) {
    current_two = i;
    return;
  }
  Swap(arr, i, Parent(i));
  SiftUp(arr, Parent(i), current_two);
}

void AddELem(int* arr, int& size, int elem, int& current_two) {
  arr[size] = elem;
  ++size;
  SiftUp(arr, size - 1, current_two);
}

void SiftDown(int* arr, int i, int size, int& current_one) {
  int largest = LeftChild(i);
  if (largest >= size) {
    current_one = i;
    return;
  }
  int right = RightChild(i);
  if (right < size && arr[right] > arr[largest]) {
    largest = right;
  }

  if (arr[largest] <= arr[i]) {
    current_one = i;
    return;
  }
  Swap(arr, i, largest);
  SiftDown(arr, largest, size, current_one);
}

void DeleteMax(int* arr, int& size, int& current_one) {
  if (size == 0) {
    return;
  }
  Swap(arr, 0, size - 1);
  --size;
  SiftDown(arr, 0, size, current_one);
}

int main() {
  int n = 0;
  int k = 0;
  std::cin >> n >> k;
  int* arr = new int[n];
  int size = 0;
  int current_two = 0;
  int current_one = 0;
  for (int i = 0; i < k; ++i) {
    int comand = 0;
    std::cin >> comand;
    if (comand == 1) {
      if (size == 0) {
        std::cout << -1 << "\n";
      } else if (size == 1) {
        std::cout << 0 << " " << arr[0] << "\n";
        --size;
      } else {
        int max_elem = arr[0];
        DeleteMax(arr, size, current_one);
        std::cout << current_one + 1 << " " << max_elem << "\n";
      }
    }
    if (comand == 2) {
      int added_elem = 0;
      std::cin >> added_elem;
      if (size == n) {
        std::cout << -1 << "\n";
      } else {
        AddELem(arr, size, added_elem, current_two);
        std::cout << current_two + 1 << "\n";
      }
    }
    if (comand == 3) {
      int deleted_elem = 0;
      std::cin >> deleted_elem;
      if (size < deleted_elem || deleted_elem == 0 || size == 0) {
        std::cout << -1 << "\n";
      } else {
        std::cout << arr[deleted_elem - 1] << "\n";
        std::swap(arr[deleted_elem - 1], arr[size - 1]);
        --size;
        if (size <= 0) {
          size = 0;
          continue;
        }
        SiftDown(arr, deleted_elem - 1, size, current_one);
        SiftUp(arr, deleted_elem - 1, current_two);
      }
    }
  }
  for (int i = 0; i < size; ++i) {
    std::cout << arr[i] << " ";
  }
  delete[] arr;
  return 0;
}