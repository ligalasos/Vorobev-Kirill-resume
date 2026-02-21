#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

class Graph {
 private:
  std::vector<std::string> color_;
  std::vector<int> time_in_;
  std::vector<int> time_up_;

 public:
  std::vector<std::vector<std::pair<int, int>>> graph;
  std::unordered_set<int> bridges;

  explicit Graph(int n) {
    time_in_.resize(n + 1);
    time_up_.resize(n + 1);
    std::vector<std::string> col(n + 1, "white");
    color_ = col;
    graph.resize(n + 1);
  }

  void DFS(Graph& graph, int current, int& time, int parent = -1) {
    color_[current] = "grey";
    time_in_[current] = ++time;
    time_up_[current] = time;
    for (auto ver : graph.graph[current]) {
      int v = ver.first;
      if (v == parent) {
        continue;
      }
      if (color_[v] == "grey") {
        time_up_[current] = std::min(time_in_[v], time_up_[current]);
      }
      if (color_[v] == "white") {
        DFS(graph, v, time, current);
        time_up_[current] = std::min(time_up_[current], time_up_[v]);
        if (time_in_[current] < time_up_[v]) {
          bridges.insert(ver.second);
        }
      }
    }
    color_[current] = "black";
  }
};

int main() {
  int n = 0;
  int m = 0;
  int time = 0;
  std::cin >> n >> m;
  Graph graph{n};
  for (int i = 1; i <= m; ++i) {
    int begin = 0;
    int end = 0;
    std::cin >> begin >> end;
    graph.graph[begin].emplace_back(end, i);
    graph.graph[end].emplace_back(begin, i);
  }
  graph.DFS(graph, 1, time);
  std::vector<int> sort_bridge(graph.bridges.begin(), graph.bridges.end());
  std::sort(sort_bridge.begin(), sort_bridge.end());
  std::cout << sort_bridge.size() << "\n";
  for (size_t i = 0; i < sort_bridge.size(); ++i) {
    std::cout << sort_bridge[i] << " ";
  }
  return 0;
}