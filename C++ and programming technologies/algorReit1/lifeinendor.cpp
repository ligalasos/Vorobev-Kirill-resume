//сдал
#include <iostream>

int Neighbours(int r, int c, int** arr, int n);

void NewArr(int n, int** arr, int** newarr);

int main() {
  int n = 0;
  int k = 0;
  std::cin >> n >> k;
  int** arr = new int*[n];
  for (int i = 0; i < n; ++i) {
    arr[i] = new int[n];
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> arr[i][j];
    }
  }
  int** newarr = new int*[n];
  for (int i = 0; i < n; i++) {
    newarr[i] = new int[n];
  }
  for (int l = 0; l < k; ++l) {
    NewArr(n, arr, newarr);
    std::swap(newarr, arr);
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cout << arr[i][j] << " ";
    }
    std::cout << "\n";
  }
  for (int i = 0; i < n; ++i) {
    delete[] arr[i];
    delete[] newarr[i];
  }
  delete[] arr;
  delete[] newarr;
  return 0;
}

int Neighbours(int r, int c, int** arr, int n) {
  int count = 0;
  if (c > 0) {
    if (arr[r][c - 1] == 1) {
      count++;
    }
  }
  if (c < n - 1) {
    if (arr[r][c + 1] == 1) {
      count++;
    }
  }
  if (r > 0) {
    if (arr[r - 1][c] == 1) {
      count++;
    }
  }
  if (r < n - 1) {
    if (arr[r + 1][c] == 1) {
      count++;
    }
  }
  if (r > 0 && c > 0) {
    if (arr[r - 1][c - 1] == 1) {
      count++;
    }
  }
  if (r > 0 && c < n - 1) {
    if (arr[r - 1][c + 1] == 1) {
      count++;
    }
  }
  if (r < n - 1 && c > 0) {
    if (arr[r + 1][c - 1] == 1) {
      count++;
    }
  }
  if (r < n - 1 && c < n - 1) {
    if (arr[r + 1][c + 1] == 1) {
      count++;
    }
  }
  return count;
}

void NewArr(int n, int** arr, int** newarr) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int m = Neighbours(i, j, arr, n);
      if (arr[i][j] == 1) {
        if (m < 2 or m > 3) {
          newarr[i][j] = 0;
        } else {
          newarr[i][j] = 1;
        }
      } else if (m == 3) {
        newarr[i][j] = 1;
      } else {
        newarr[i][j] = 0;
      }
    }
  }
}