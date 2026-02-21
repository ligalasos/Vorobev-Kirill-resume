#include <iostream>
#include <algorithm>

int main() {
  int n = 0;
  std::cin >> n;
  int* arr = new int[n];
  for (int i = 0; i < n; i++) {
    std::cin >> arr[i];
  }
  int* dp = new int[n];
  int* prev = new int[n];
  for (int i = 0; i < n; ++i) {
    dp[i] = 1;
    prev[i] = -1;
  }
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      if (arr[j] < arr[i] && dp[j] + 1 > dp[i]) {
        dp[i] = dp[j] + 1;
        prev[i] = j;
      }
    }
  }
  int max_len = *std::max_element(dp, dp + n);
  auto max_index = std::distance(dp, std::max_element(dp, dp + n));
  int* result = new int[max_len];
  int k = 0;
  auto current_index = max_index;
  while (current_index != -1) {
    result[k++] = arr[current_index];
    current_index = prev[current_index];
  }
  for (int i = k - 1; i >= 0; --i) {
    std::cout << result[i] << (i == 0 ? "" : " ");
  }
  delete[] arr;
  delete[] dp;
  delete[] prev;
  delete[] result;
  return 0;
}

