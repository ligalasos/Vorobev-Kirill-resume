#include <iostream>
#include <vector>
#include <string>
#include <deque>

class Graph {
 public:
  std::vector<std::vector<int>> v;
  std::vector<int> parents;
  std::vector<std::string> color;

  explicit Graph(int n) {
    v.resize(n + 1);
    parents.resize(n + 1);
    std::vector<std::string> col(n + 1, "white");
    color = col;
  }
};

void DFS(Graph& graph, int& current, int& last, int& first, bool& iscycle) {
  graph.color[current] = "gray";
  for (auto ver : graph.v[current]) {
    if (graph.color[ver] == "gray") {
      iscycle = true;
      last = ver;
      first = current;
      graph.color[current] = "black";
      return;
    }
    if (graph.color[ver] == "white") {
      graph.parents[ver] = current;
      DFS(graph, ver, last, first, iscycle);
    }
  }
  graph.color[current] = "black";
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Graph graph{n};
  int first = 0;
  int last = 0;
  bool iscycle = false;
  int current = 0;
  for (int i = 0; i < m; ++i) {
    int begin = 0;
    int end = 0;
    std::cin >> begin >> end;
    graph.v[begin].push_back(end);
  }

  for (int i = 1; i <= n; ++i) {
    current = i;
    DFS(graph, current, last, first, iscycle);
    if (iscycle) {
      break;
    }
  }
  std::deque<int> reverce;
  int k = first;
  while (true) {
    reverce.push_front(k);
    if (k == last) {
      break;
    }
    k = graph.parents[k];
  }
  if (iscycle) {
    std::cout << "YES\n";
    for (size_t i = 0; i < reverce.size(); ++i) {
      std::cout << reverce[i] << " ";
    }
  } else {
    std::cout << "NO";
  }
  return 0;
}