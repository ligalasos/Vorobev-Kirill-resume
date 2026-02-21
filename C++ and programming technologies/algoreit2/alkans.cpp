#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>

void DFS(std::vector<std::vector<size_t>>& v, std::vector<std::string>& color, size_t& current, bool& iscycle,
         size_t parent = 0) {
  color[current] = "gray";
  for (auto ver : v[current]) {
    if (ver == parent) {
      continue;
    }
    if (color[ver] == "gray") {
      iscycle = true;
      color[current] = "black";
      return;
    }
    if (color[ver] == "white") {
      DFS(v, color, ver, iscycle, current);
    }
  }
  color[current] = "black";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  size_t n = 0;
  size_t m = 0;
  size_t current = 0;
  bool iscycle = false;
  std::cin >> n >> m;
  std::vector<std::vector<size_t>> graph(n + 1);
  std::vector<char> element_type(n + 1);
  std::vector<std::string> color(n + 1, "white");
  std::string alk;
  std::cin >> alk;
  for (size_t i = 0; i < alk.size(); ++i) {
    if (alk[i] == 'C') {
      element_type[i + 1] = 'C';
    } else {
      element_type[i + 1] = 'H';
    }
  }
  std::vector<std::pair<int, int>> edges;
  for (size_t i = 1; i <= m; ++i) {
    size_t begin = 0;
    size_t end = 0;
    std::cin >> begin >> end;
    edges.emplace_back(begin, end);
    graph[begin].push_back(end);
    graph[end].push_back(begin);
  }
  if (m != n - 1) {
    std::cout << "NO";
    return 0;
  }
  bool norm = true;
  for (size_t i = 0; i < edges.size(); ++i) {
    size_t begin = edges[i].first;
    size_t end = edges[i].second;
    if ((element_type[begin] == 'H' and element_type[end] == 'H')) {
      norm = false;
    }
  }
  if (norm) {
    for (size_t i = 1; i <= n; ++i) {
      if ((element_type[i] == 'H' and graph[i].size() != 1) or (element_type[i] == 'C' and graph[i].size() != 4)) {
        norm = false;
      }
    }
  }
  if (!norm) {
    std::cout << "NO";
    return 0;
  }
  size_t visited = 0;
  for (size_t i = 1; i <= n; ++i) {
    if (color[i] == "white") {
      current = i;
      DFS(graph, color, current, iscycle);
      visited++;
      if (iscycle) {
        break;
      }
    }
  }
  if (iscycle or visited != 1) {
    std::cout << "NO\n";
  } else {
    std::cout << "YES";
  }
  return 0;
}