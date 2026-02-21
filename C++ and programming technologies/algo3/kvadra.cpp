#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>



int main() {
  int n = 1;
    for (int i = 1; i <= 11; ++i) {
      n *= i;
    }
    std::cout << n;
    return 0;
}