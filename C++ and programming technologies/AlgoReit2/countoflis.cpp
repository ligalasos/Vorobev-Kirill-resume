#include <algorithm>
#include <iostream>
#include <climits>
#include <deque>
#include <cmath>

int main() {
  std::ios_base::sync_with_stdio(false), std::cin.tie(nullptr);
  srand(time(nullptr));
  int32_t n = 0;
  std::cin >> n;
  std::deque<int32_t> a(n);
  std::deque<int32_t> dp(n);
  for (int32_t i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  // будем хранить в дп типо значения колва возрастающих последовательностей до i элемента
  dp[0] = 1;
  int sum = 1;
  for (int32_t i = 1; i < n; ++i) {
    for (int32_t j = 0; j < i; ++j) {
      if (a[i] > a[j]) {
        dp[i] += dp[j] % 1000000;
      }
    }
    dp[i] += 1;
    sum += dp[i];
  }
  std::cout << sum % 1000000;
}
