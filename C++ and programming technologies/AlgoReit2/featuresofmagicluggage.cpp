#include <iostream>
#include <vector>

int main() {
  int n = 0;
  int m = 0;
  std::vector<int> weight(n);
  std::vector<int> cost(m);
  for (int i = 0; i < n; ++i) {
    std::cin >> weight[i];
  }
  for (int i = 0; i < n; ++i) {
    std::cin >> cost[i];
  }
  
  return 0;
}