#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void DFS(std::vector<std::vector<int>>& graph, std::vector<std::string>& color, std::vector<int>& temporary,
         int current) {
  color[current] = "black";
  temporary.push_back(current);
  for (auto ver : graph[current]) {
    if (color[ver] == "white") {
      DFS(graph, color, temporary, ver);
    }
  }
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<std::vector<int>> graph(n + 1);
  std::vector<std::string> color(n + 1, "white");
  std::vector<std::vector<int>> comp;
  for (int i = 0; i < m; ++i) {
    int begin = 0;
    int end = 0;
    std::cin >> begin >> end;
    graph[begin].push_back(end);
    graph[end].push_back(begin);
  }
  for (int i = 1; i <= n; ++i) {
    if (color[i] == "white") {
      std::vector<int> temporary;
      DFS(graph, color, temporary, i);
      comp.push_back(temporary);
    }
  }

  std::cout << comp.size() << "\n";
  for (auto temp : comp) {
    std::cout << temp.size() << "\n";
    for (auto ver : temp) {
      std::cout << ver << " ";
    }
    std::cout << "\n";
  }
  return 0;
}