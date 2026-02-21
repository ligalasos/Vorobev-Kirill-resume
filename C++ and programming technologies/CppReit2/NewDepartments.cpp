#include <iostream>
#include <deque>
#include <algorithm>

int main() {
  int n = 0;
  std::cin >> n;
  int value = 0;
  std::deque<int32_t> arr(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  int m = 0;
  std::cin >> m;
  for (int i = 0; i < m; ++i) {
    std::cin >> value;
    auto a = std::lower_bound(arr.begin(), arr.end(), value);
    auto b = std::upper_bound(arr.begin(), arr.end(), value);
    std::cout << b - a << "\n";
  }
  return 0;
}