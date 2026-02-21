#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <map>
#include <bitset>

void DFS(std::vector<std::vector<size_t>>& v, std::vector<std::string>& color, size_t& current, bool& iscycle) {
  color[current] = "gray";
  for (auto ver : v[current]) {
    if (color[ver] == "gray") {
      iscycle = true;
      color[current] = "black";
      return;
    }
    if (color[ver] == "white") {
      DFS(v, color, ver, iscycle);
    }
  }
  color[current] = "black";
}

int main() {
  size_t n = 0;
  std::cin >> n;
  std::vector<std::vector<size_t>> graph(n + 1);
  std::vector<std::string> color(n + 1, "white");
  bool iscycle = false;
  size_t current = 0;
  for (size_t i = 1; i < n; ++i) {
    std::string str;
    std::cin >> str;
    for (size_t j = 0; j < str.size(); ++j) {
      if (str[j] == 'R') {
        graph[i].push_back(i + j + 1);
      } else {
        graph[i + j + 1].push_back(i);
      }
    }
  }
  for (size_t i = 1; i <= n; ++i) {
    current = i;
    DFS(graph, color, current, iscycle);
    if (iscycle) {
      break;
    }
  }
  if (iscycle) {
    std::cout << "NO\n";
  } else {
    std::cout << "YES";
  }
  return 0;
}