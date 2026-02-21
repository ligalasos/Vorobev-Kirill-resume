#include <iostream>

void Yarchik(int n);

void YarchikDel(int n);

int main() {
  int n = 0;
  std::cin >> n;
  Yarchik(n);
  return 0;
}

void YarchikDel(int n) {
  if (n == 2) {
    std::cout << -2 << " " << -1 << " ";
    return;
  }
  if (n == 1) {
    std::cout << -1 << " ";
    return;
  }
  YarchikDel(n - 2);
  std::cout << -n << " ";
  Yarchik(n - 2);
  YarchikDel(n - 1);
}

void Yarchik(int n) {
  if (n == 2) {
    std::cout << "1 2 ";
    return;
  }
  if (n == 0) {
    return;
  }
  if (n == 1) {
    std::cout << 1 << " ";
    return;
  }
  Yarchik(n - 1);
  YarchikDel(n - 2);
  std::cout << n << " ";
  Yarchik(n - 2);
}