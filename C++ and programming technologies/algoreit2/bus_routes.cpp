#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <bitset>
#include <unordered_set>

void BFS() {

}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> m >> n;
  std::vector<std::vector<std::pair<int, bool>>> graph(n + 1);
  std::vector<bool> visited(n + 1);
  
  int current = 0;
  int next = 0;
  for (int i = 0; i < n; ++i) {
    std::cin >> current;
    for (int i = 0; i < m; ++i) {
      std::cin >> next;
    }
  }

  
  return 0;
}