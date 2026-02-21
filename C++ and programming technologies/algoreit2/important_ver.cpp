#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

void DFSONE(std::unordered_set<int64_t>& articulation_points, std::vector<std::string>& color,
            std::vector<std::vector<int64_t>>& graph, std::vector<int64_t>& time_in, std::vector<int64_t>& time_up,
            int64_t current, int64_t& time, bool is_root, std::vector<int64_t>& size_tree,
            std::vector<int64_t>& parents) {
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
      DFSONE(articulation_points, color, graph, time_in, time_up, ver, time, false, size_tree, parents);
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
  std::vector<std::vector<int64_t>> graph(n + 1);
  std::vector<std::string> color(n + 1, "white");
  std::vector<int64_t> time_in(n + 1);
  std::vector<int64_t> time_up(n + 1);
  std::unordered_set<int64_t> articulation_points;
  std::vector<int64_t> size_tree(n + 1);
  std::vector<int64_t> parents(n + 1);
  for (int64_t i = 0; i < m; ++i) {
    int64_t begin = 0;
    int64_t end = 0;
    std::cin >> begin >> end;
    graph[begin].push_back(end);
    graph[end].push_back(begin);
  }
  DFSONE(articulation_points, color, graph, time_in, time_up, 1, time, true, size_tree, parents);
  std::vector<int64_t> ans(n + 1);
  for (int64_t i = 1; i <= n; ++i) {
    if (!articulation_points.count(i)) {
      ans[i] = n - 1;
      continue;
    }
    int64_t sum = 0;
    int64_t dad = n - size_tree[i];
    for (auto ver : graph[i]) {
      if (ver == parents[i] or parents[ver] != i) {
        continue;
      }
      sum += dad * size_tree[ver];
      sum += size_tree[ver] * (n - 1 - size_tree[ver]);
    }
    ans[i] = (sum / 2) + (n - 1);
  }
  for (int i = 1; i < n + 1; ++i) {
    std::cout << ans[i] << "\n";
  }
  return 0;
}