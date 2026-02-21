#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <unordered_map>

struct Edge {
  int start = 0;
  int finish = 0;
  int weight = 0;
  Edge(int s, int f, int w) : start(s), finish(f), weight(w) {
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n = 0;
  int m = 0;
  int k = 0;
  int begin = 0;
  int end = 0;
  std::cin >> n >> m >> k >> begin >> end;

  std::unordered_map<int, std::unordered_map<int, int>> min_edges;
  for (int i = 0; i < m; ++i) {
    int s = 0;
    int f = 0;
    int w = 0;
    std::cin >> s >> f >> w;
    if (!min_edges[s].count(f) || w < min_edges[s][f]) {
      min_edges[s][f] = w;
    }
  }

  std::vector<Edge> edges;
  for (const auto& [u, neighbors] : min_edges) {
    for (const auto& [v, w] : neighbors) {
      edges.emplace_back(u, v, w);
    }
  }

  std::vector<std::vector<int64_t>> dp(k + 1, std::vector<int64_t>(n + 1, LLONG_MAX));
  dp[0][begin] = 0;

  for (int i = 1; i <= k; ++i) {
    dp[i].assign(n + 1, LLONG_MAX);
    for (const auto& [start, finish, weight] : edges) {
      if (dp[i - 1][start] != LLONG_MAX && dp[i - 1][start] + weight < dp[i][finish]) {
        dp[i][finish] = dp[i - 1][start] + weight;
      }
    }
  }

  int64_t min_cost = LLONG_MAX;
  for (int i = 0; i <= k; ++i) {
    min_cost = std::min(min_cost, dp[i][end]);
  }

  if (min_cost != LLONG_MAX) {
    std::cout << min_cost;
    return 0;
  }
  std::cout << -1;
  return 0;
}