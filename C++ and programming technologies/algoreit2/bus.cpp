#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <numeric>

void DFS(size_t u, std::vector<std::unordered_map<size_t, size_t>>& graph, std::vector<size_t>& path) {
  while (!graph[u].empty()) {
    auto it = graph[u].begin();
    size_t v = it->first;
    graph[u][v]--;
    if (graph[u][v] == 0) {
      graph[u].erase(it);
    }
    DFS(v, graph, path);
  }
  path.push_back(u);
}

bool IsStronglyConnected(size_t start, const std::vector<std::unordered_map<size_t, size_t>>& graph,
                         const std::vector<size_t>& non_zero) {
  std::vector<bool> visited(graph.size(), false);
  std::queue<size_t> q;
  q.push(start);
  visited[start] = true;

  while (!q.empty()) {
    size_t u = q.front();
    q.pop();
    for (auto& edge : graph[u]) {
      size_t v = edge.first;
      if (!visited[v] && edge.second > 0) {
        visited[v] = true;
        q.push(v);
      }
    }
  }
  for (size_t u : non_zero) {
    if (!visited[u]) {
      return false;
    }
  }
  return true;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  size_t n = 0;
  size_t m = 0;
  std::cin >> n >> m;
  std::vector<std::unordered_map<size_t, size_t>> graph(m + 1);
  std::vector<size_t> out_degree(m + 1, 0);
  std::vector<size_t> in_degree(m + 1, 0);
  for (size_t i = 0; i < n; ++i) {
    size_t k = 0;
    std::cin >> k;
    size_t current = 0;
    std::cin >> current;
    for (size_t j = 0; j < k; ++j) {
      size_t next = 0;
      std::cin >> next;
      ++graph[current][next];
      ++out_degree[current];
      ++in_degree[next];
      current = next;
    }
  }
  if (n == 0) {
    std::cout << "0\n";
    return 0;
  }
  std::vector<size_t> non_zero;
  for (size_t u = 1; u <= m; ++u) {
    if (in_degree[u] != out_degree[u]) {
      std::cout << "0\n";
      return 0;
    }
    if (in_degree[u] + out_degree[u] > 0) {
      non_zero.push_back(u);
    }
  }
  if (non_zero.empty()) {
    std::cout << "1 1\n";
    return 0;
  }
  size_t start = non_zero[0];
  if (!IsStronglyConnected(start, graph, non_zero)) {
    std::cout << "0\n";
    return 0;
  }
  std::vector<std::unordered_map<size_t, size_t>> transposed(m + 1);
  for (size_t u = 1; u <= m; ++u) {
    for (auto& edge : graph[u]) {
      size_t v = edge.first;
      transposed[v][u] += edge.second;
    }
  }
  if (!IsStronglyConnected(start, transposed, non_zero)) {
    std::cout << "0\n";
    return 0;
  }
  std::vector<size_t> path;
  DFS(start, graph, path);
  std::reverse(path.begin(), path.end());
  if (path.empty() || path.front() != path.back()) {
    std::cout << "0\n";
    return 0;
  }
  size_t total_edges = std::accumulate(out_degree.begin(), out_degree.end(), 0);
  if (path.size() != total_edges + 1) {
    std::cout << "0\n";
    return 0;
  }
  std::cout << path.size();
  for (size_t stop : path) {
    std::cout << " " << stop;
  }
  std::cout << "\n";

  return 0;
}