#include <iostream>
#include <deque>

int main() {
  int n = 0;
  std::cin >> n;
  int* arr_one = new int[n + 1];
  for (int i = 1; i < n + 1; ++i) {
    std::cin >> arr_one[i];
  }
  int m = 0;
  std::cin >> m;
  int* arr_two = new int[m + 1];
  for (int i = 1; i < m + 1; ++i) {
    std::cin >> arr_two[i];
  }
  int** dp = new int*[n + 1];
  for (int i = 0; i < n + 1; ++i) {
    dp[i] = new int[m + 1];
  }
  for (int i = 0; i < n + 1; ++i) {
    dp[i][0] = 0;
  }
  for (int i = 0; i < m + 1; ++i) {
    dp[0][i] = 0;
  }
  for (int i = 1; i < n + 1; ++i) {
    for (int j = 1; j < m + 1; ++j) {
      if (arr_one[i] == arr_two[j]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }
  // for (int i = 0; i < n + 1; ++i) {
  //   for (int j = 0; j < m + 1; ++j) {
  //     std::cout << dp[i][j] << " ";
  //   }
  //   std::cout << "\n";
  // }
  // std::cout << "\n";
  int value = dp[n][m];
  int count = value;
  int* arr = new int[value];
  int counter = 0;
  int i = n;
  int j = m;
  while (counter < n + m + 2 and (i != 0 and j != 0)) {
    if (dp[i][j] == dp[i - 1][j]) {
      i -= 1;
    } else if (dp[i][j] == dp[i][j - 1]) {
      j -= 1;
    } else {
      i -= 1;
      j -= 1;
      arr[value - 1] = arr_one[i + 1];
      --value;
    }
    ++counter;
  }
  for (int i = 0; i < count; ++i) {
    std::cout << arr[i] << " ";
  }
  delete[] arr;
  delete[] arr_one;
  delete[] arr_two;
  for (int i = 0; i < n; ++i) {
    delete[] dp[i];
  }
  delete[] dp;
  return 0;
}