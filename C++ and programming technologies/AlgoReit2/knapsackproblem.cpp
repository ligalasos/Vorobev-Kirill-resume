#include <algorithm>
#include <iostream>
#include <climits>
#include <deque>
#include <cmath>

int main() {
  std::ios_base::sync_with_stdio(false), std::cin.tie(nullptr);
  srand(time(nullptr));
  int32_t n = 0;
  int32_t m = 0;
  std::cin >> n;
  std::cin >> m;
  std::deque<int32_t> weight(n + 1);
  std::deque<int32_t> cost(n + 1);
  std::deque<std::deque<int32_t>> dp(n + 1, std::deque<int32_t>(m + 1));
  dp[0][0] = 0;
  for (int i = 1; i <= m; ++i) {
    dp[0][i] = INT_MIN;
  }
  for (int i = 1; i < n; ++i) {
    dp[i][0] = 0;
  }
  for (int32_t i = 1; i <= n; ++i) {
    std::cin >> weight[i];
  }
  for (int32_t i = 1; i <= n; i++) {
    std::cin >> cost[i];
  }
  for (int32_t i = 1; i <= n; ++i) {
    for (int32_t j = m; j > 0; --j) {
      if (j >= weight[i]) {
        int32_t mass = weight[i];
        if (dp[i - 1][j - mass] != INT_MIN) {
          dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - mass] + cost[i]);
        } else {
          dp[i][j] = std::max(INT_MIN, dp[i - 1][j]);
        }
        continue;
      }
      dp[i][j] = std::max(dp[i - 1][j], INT_MIN);
    }
  }
  int32_t ans = 0;
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      std::cout << dp[i][j] << " ";

    }
    std::cout << "\n";
  }

  std::cout << "\n";
  int c = 0;
  for (int i = 0; i <= m; ++i) {
    if (dp[n][i] > ans) {
      ans = dp[n][i];
      c = i;
    }
  }
  int j = c;
  int i = n;
  while (j > 0) {
    if (dp[i][j] == dp[i - 1][j]) {
      --i;
    } else {
      std::cout << i << "\n";
      j = j - weight[i];
      --i;
    }
  }
}