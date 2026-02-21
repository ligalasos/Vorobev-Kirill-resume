#include <iostream>
#include <vector>

int main() {
  int n = 0;
  std::cin >> n;
  std::vector<int64_t> dp(n);
  dp[0] = 2;
  dp[1] = 3;
  for (int i = 2; i < n; ++i) {
    dp[i] = dp[i - 2] + dp[i - 1];
  }
  std::cout << dp[n - 1];
  return 0;
}
// 34
// 14930352
