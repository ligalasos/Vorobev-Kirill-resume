//сдал
#include <iostream>

void Sabbak(int n, int from, int to);

int main() {
  int n = 0;
  std::cin >> n;
  Sabbak(n, 1, 3);
  return 0;
}

void Sabbak(int n, int from, int to) {
  if (n == 0) {
    return;
  }
  int prom = 6 - from - to;
  if (n == 1) {
    std::cout << 1 << " " << from << " " << to << "\n";
  } else {
    Sabbak(n - 1, from, to);
    std::cout << n << " " << from << " " << prom << "\n";
    Sabbak(n - 1, to, from);
    std::cout << n << " " << prom << " " << to << "\n";
    Sabbak(n - 1, from, to);
  }
}