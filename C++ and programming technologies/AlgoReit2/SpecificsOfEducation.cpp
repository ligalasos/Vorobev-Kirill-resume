#include <algorithm>
#include <iostream>
#include <climits>
#include <deque>
#include <cmath>

int main() {
  std::ios_base::sync_with_stdio(false), std::cin.tie(nullptr);
  srand(time(nullptr));
  int n = 0;
  std::cin >> n;
  std::deque<int> arr(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  int count = n - 1;
  std::deque<std::deque<int>> dp(count + 1, std::deque<int>(count + 1, INT_MAX));
  for (int i = 0; i < n; ++i) {
    dp[i][i] = 0;
  }
  for (int len = 2; len <= count; ++len) {
    for (int i = 1; i <= count - len + 1; ++i) {
      int j = i + len - 1;
      for (int r = i; r < j; ++r) {
        dp[i][j] = std::min(dp[i][j], dp[i][r] + dp[r + 1][j] + arr[i - 1] * arr[r] * arr[j]);
      }
    }
  }
  std::cout << dp[1][n - 1];
  return 0;
}