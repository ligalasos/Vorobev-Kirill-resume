#include <iostream>
#include <vector>
#include <string>
#include <set>

class Graph {
 public:
  std::vector<size_t> articulation_points;
  std::vector<std::string> color;
  std::vector<std::vector<size_t>> graph;
  std::vector<size_t> time_in;
  std::vector<size_t> time_up;

  explicit Graph(size_t n, size_t m) {
    graph.resize(n + m + 1);
    std::vector<std::string> col(n + 1 + m, "white");
    color = col;
    time_in.resize(n + 1 + m);
    time_up.resize(n + 1 + m);
  }
};

void Removeduplicates(std::vector<size_t>& vec) {
  std::set<int> s(vec.begin(), vec.end());
  vec.assign(s.begin(), s.end());
}

void DFSONE(Graph& graph, size_t current, size_t& time, bool is_root, size_t& n) {
  graph.color[current] = "grey";
  graph.time_in[current] = graph.time_up[current] = ++time;
  int children = 0;
  for (auto ver : graph.graph[current]) {
    if (graph.color[ver] == "grey") {
      graph.time_up[current] = std::min(graph.time_up[current], graph.time_in[ver]);
    }
    if (graph.color[ver] == "white") {
      ++children;
      DFSONE(graph, ver, time, false, n);
      graph.time_up[current] = std::min(graph.time_up[current], graph.time_up[ver]);
      if (!is_root and graph.time_in[current] <= graph.time_up[ver]) {
        if (current > n) {
          graph.articulation_points.push_back(current);
        }
      }
    }
  }
  if (is_root and children > 1 and current > n) {
    graph.articulation_points.push_back(current);
  }
  graph.color[current] = "black";
}

int main() {
  size_t n = 0;
  size_t m = 0;
  size_t time = 0;
  std::cin >> n >> m;
  Graph graph(n, m);
  for (size_t i = 1; i <= m; ++i) {
    size_t one = 0;
    size_t two = 0;
    size_t three = 0;
    std::cin >> one >> two >> three;
    graph.graph[i + n].push_back(one);
    graph.graph[i + n].push_back(two);
    graph.graph[i + n].push_back(three);
    graph.graph[one].push_back(i + n);
    graph.graph[two].push_back(i + n);
    graph.graph[three].push_back(i + n);
  }
  DFSONE(graph, 1, time, true, n);
  if (graph.articulation_points.empty()) {
    std::cout << 0;
    return 0;
  }
  Removeduplicates(graph.articulation_points);
  std::cout << graph.articulation_points.size() << "\n";
  for (auto pad : graph.articulation_points) {
    std::cout << pad - n << " ";
  }
  return 0;
}