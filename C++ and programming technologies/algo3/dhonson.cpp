#include <iostream>
#include <vector>
#include <queue>
#include <climits>

int64_t Jo(std::vector<std::vector<std::pair<int64_t, int64_t>>>& graph, int64_t n) {
  std::vector<int64_t> potencia(n + 1, INT_MAX);
  potencia[0] = 0;
  for (int64_t i = 0; i < n; ++i) {
    for (int64_t j = 0; j <= n; ++j) {
      for (auto [ver, weight] : graph[j]) {
        if (potencia[j] != INT_MAX and potencia[ver] > potencia[j] + weight) {
          potencia[ver] = potencia[j] + weight;
        }
      }
    }
  }

  for (int64_t i = 0; i < n; ++i) {
    for (auto& edge : graph[i]) {
      edge.second = edge.second + potencia[i] - potencia[edge.first];
    }
  }

  std::vector<std::vector<int64_t>> dist(n + 1, std::vector<int64_t>(n + 1, INT_MAX));
  for (int64_t i = 0; i < n; ++i) {
    std::priority_queue<std::pair<int64_t, int64_t>, std::vector<std::pair<int64_t, int64_t>>,
                        std::greater<std::pair<int64_t, int64_t>>>
        q;
    q.emplace(0, i);
    dist[i][i] = 0;
    while (!q.empty()) {
      int64_t current = q.top().first;
      int64_t ver = q.top().second;
      q.pop();
      if (current > dist[i][ver]) {
        continue;
      }
      for (auto& [to, weight] : graph[ver]) {
        if (dist[i][ver] + weight < dist[i][to]) {
          dist[i][to] = dist[i][ver] + weight;
          q.emplace(dist[i][ver] + weight, to);
        }
      }
    }
  }
  int64_t min_dist = 0;
  for (int64_t i = 0; i < n; ++i) {
    for (int64_t j = 0; j < n; ++j) {
      if (dist[i][j] != INT_MAX) {
        dist[i][j] = dist[i][j] - potencia[i] + potencia[j];
      }
      if (i != j and dist[i][j] != INT_MAX) {
        min_dist = std::max(dist[i][j], min_dist);
      }
    }
  }
  return min_dist;
}

int main() {
  int64_t n = 0;
  int64_t m = 0;
  std::cin >> n >> m;
  std::vector<std::vector<std::pair<int64_t, int64_t>>> graph(n + 1);
  for (int64_t i = 0; i < m; ++i) {
    int64_t begin = 0;
    int64_t end = 0;
    int64_t weight = 0;
    std::cin >> begin >> end >> weight;
    graph[begin].emplace_back(end, weight);
  }

  for (int64_t i = 0; i < n; ++i) {
    graph[n].emplace_back(i, 0);
  }

  std::cout << Jo(graph, n);
  return 0;
}