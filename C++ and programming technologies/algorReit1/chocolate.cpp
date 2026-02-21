#include <iostream>

int main() {
  int n = 0;
  int k = 0;
  int m = 0;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::cin >> m >> k;
    std::cout << (k * m) - 1 << "\n";
  }
  return
}