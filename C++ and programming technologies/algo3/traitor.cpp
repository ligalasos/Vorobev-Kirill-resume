#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

std::vector<int> dist;
std::vector<int> prev;

class Edge {
 public:
  int one = 0;
  int two = 0;
  int weight = 0;

  explicit Edge(int one, int two, int weight) : one(one), two(two), weight(weight) {
  }
};

std::vector<Edge> edges;

bool Relax(int one, int two, int weight) {
  if (dist[one] != 100000) {
    if (dist[two] > dist[one] + weight) {
      dist[two] = dist[one] + weight;
      prev[two] = one;
      return true;
    }
  }
  return false;
}

void Ford(int n) {
  for (int i = 0; i < n - 1; ++i) {
    for (auto edge : edges) {
      Relax(edge.one, edge.two, edge.weight);
    }
  }
}

std::vector<int> cycle;

bool Iscycle(int& begin_cycle) {
  for (auto edge : edges) {
    if (dist[edge.one] != INT_MAX and Relax(edge.one, edge.two, edge.weight)) {
      begin_cycle = edge.two;
      return true;
    }
  }
  return false;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n = 0;
  std::cin >> n;
  dist.resize(n + 1, 100000);
  prev.resize(n + 1);
  dist[1] = 0;
  int begin_cucle = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      int weight = 0;
      std::cin >> weight;
      if (weight != 100000) {
        edges.emplace_back(i, j, weight);
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    edges.emplace_back(0, i, 0);
  }
  dist[0] = 0;
  Ford(n);
  if (Iscycle(begin_cucle)) {
    std::cout << "YES\n";
    std::vector<int> cycle;
    int k = begin_cucle;

    for (int i = 0; i < n; ++i) {
      k = prev[k];
    }

    int start = k;

    do {
      cycle.push_back(k);
      k = prev[k];
    } while (k != start);

    cycle.push_back(start);
    std::reverse(cycle.begin(), cycle.end());
    std::cout << cycle.size() << "\n";

    for (int v : cycle) {
      std::cout << v << " ";
    }
  } else {
    std::cout << "NO";
  }
  return 0;
}