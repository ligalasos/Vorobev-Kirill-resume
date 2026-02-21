#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

std::vector<std::vector<int64_t>> graph;
std::vector<std::string> color;
std::vector<int64_t> time_in;
std::vector<int64_t> time_up;
std::unordered_set<int64_t> articulation_points;
std::vector<int64_t> size_tree;
std::vector<int64_t> parents;

void DFSONE(int64_t current, int64_t& time, bool is_root) {
  color[current] = "grey";
  time_in[current] = time_up[current] = ++time;
  int64_t children = 0;
  size_tree[current] = 1;
  for (auto ver : graph[current]) {
    if (color[ver] == "grey") {
      time_up[current] = std::min(time_up[current], time_in[ver]);
    }
    if (color[ver] == "white") {
      parents[ver] = current;
      ++children;
      DFSONE(ver, time, false);
      time_up[current] = std::min(time_up[current], time_up[ver]);
      size_tree[current] += size_tree[ver];
      if (!is_root and time_in[current] <= time_up[ver]) {
        articulation_points.insert(current);
      }
    }
  }
  if (is_root and children > 1) {
    articulation_points.insert(current);
  }
  color[current] = "black";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int64_t n = 0;
  int64_t m = 0;
  int64_t time = 0;
  std::cin >> n >> m;
  graph.resize(n + 1);
  color.resize(n + 1, "white");
  time_in.resize(n + 1);
  time_up.resize(n + 1);
  size_tree.resize(n + 1);
  parents.resize(n + 1);
  for (int64_t i = 0; i < m; ++i) {
    int64_t begin = 0;
    int64_t end = 0;
    std::cin >> begin >> end;
    graph[begin].push_back(end);
    graph[end].push_back(begin);
  }
  DFSONE(1, time, true);
  std::vector<int64_t> ans(n + 1);
  for (int v = 1; v <= n; ++v) {
    if (!articulation_points.count(v)) {
      ans[v] = n - 1;
      continue;
    }
    std::vector<int64_t> components;
    int64_t sum_child = 0;
    for (int64_t u : graph[v]) {
      if (parents[u] == v && time_up[u] >= time_in[v]) {
        components.push_back(size_tree[u]);
        sum_child += size_tree[u];
      }
    }
    if (parents[v] != -1) {
      int64_t rest = n - 1 - sum_child;
      if (rest > 0) {
        components.push_back(rest);
      }
    }
    int64_t sum_sq = 0;
    for (int64_t c : components) {
      sum_sq += c * c;
    }
    int64_t total = n - 1;
    int64_t pairs = (total * total - sum_sq) / 2;
    ans[v] = pairs + (n - 1);
  }
  for (int i = 1; i <= n; ++i) {
    std::cout << ans[i] << '\n';
  }
  return 0;
}