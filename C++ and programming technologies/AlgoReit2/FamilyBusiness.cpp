#include <algorithm>
#include <iostream>
#include <climits>
#include <deque>
#include <cmath>

int64_t Pow(int64_t x, int64_t y) {
  int64_t result = 1;
  while (y > 0) {
    if (y % 2 == 1) {
      result = (result * x);
    }
    x = (x * x);
    y /= 2;
  }
  return result;
}

int main() {
  std::ios_base::sync_with_stdio(false), std::cin.tie(nullptr);
  srand(time(nullptr));
  int64_t n = 0;
  int64_t m = 0;
  std::cin >> n >> m;
  int str = n - 1;
  int col = m - 1;
  int count_of_zam = (n - 1) * (m - 1);
  int64_t sum = Pow(2, n * m);
  
  return 0;
}
