#include <iostream>
#include <vector>
#include <deque>
#include <string>

void DFS(std::vector<std::vector<int>>& v, std::vector<std::string>& color, int& current) {
  color[current] = "grey";
  for (auto ver : v[current]) {
    if (color[ver] == "white") {
      DFS(v, color, ver);
    }
  }
}

int Count(int n, std::vector<std::vector<int>>& v, std::vector<std::string>& color) {
  int counter = 0;
  for (int i = 1; i <= n; ++i) {
    if (color[i] == "white") {
      ++counter;
      DFS(v, color, i);
    }
  }
  return counter;
}

int main() {
  int n = 0;
  std::cin >> n;
  std::vector<std::vector<int>> v(n + 1);
  std::vector<std::string> color(n + 1, "white");
  for (int i = 1; i <= n; ++i) {
    int k = 0;
    std::cin >> k;
    v[i].push_back(k);
    v[k].push_back(i);
  }
  std::cout << Count(n, v, color);
  return 0;
}