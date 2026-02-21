#include <algorithm>
#include <iostream>
#include <climits>
#include <deque>

int main() {
  std::ios_base::sync_with_stdio(false), std::cin.tie(nullptr);
  srand(time(nullptr));
  int32_t n{};
  std::cin >> n;
  std::deque<int32_t> a(n + 1);
  std::deque<int32_t> dp(n + 1, INT_MAX);
  for (int32_t i = 1; i <= n; ++i) {
    std::cin >> a[i];
  }
  dp[0] = INT_MIN;
  for (int32_t i = 1; i <= n; ++i) {
    auto j = std::lower_bound(dp.begin(), dp.end(), a[i]) - dp.begin();
    dp[j] = a[i];
  }
  int32_t ans = 0;
  for (int32_t i = 1; i <= n; ++i) {
    if (dp[i] != INT_MAX) {
      ans = i;
    }
  }
  std::cout << ans;
}