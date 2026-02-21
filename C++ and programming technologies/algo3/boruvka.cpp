#include <iostream>
#include <vector>
#include <algorithm>

struct Edge {
  int64_t start;
  int64_t finish;
  int64_t weight;

  explicit Edge(int64_t start, int64_t finish, int64_t weight) : start(start), finish(finish), weight(weight) {
  }
};

std::vector<Edge> edges;

class Dsu {
 private:
  std::vector<int64_t> parent_;
  std::vector<int64_t> size_;
  std::vector<int64_t> sum_;

 public:
  explicit Dsu(int64_t n) {
    parent_.resize(n + 1);
    size_.resize(n + 1, 1);
    sum_.resize(n + 1, 0);
    for (int64_t i = 1; i <= n; ++i) {
      parent_[i] = i;
    }
  }

  int64_t Getsum(const int64_t& x) {
    return sum_[Find(x)];
  }

  void Unite(const int64_t& x, const int64_t& y, const int64_t& w) {
    int64_t x_root = Find(x);
    int64_t y_root = Find(y);
    if (x_root == y_root) {
      return;
    }
    if (size_[x_root] < size_[y_root]) {
      std::swap(x_root, y_root);
    }
    parent_[y_root] = x_root;
    size_[x_root] += size_[y_root];
    sum_[x_root] += sum_[y_root] + w;
  }

  int64_t Find(const int64_t& x) {
    if (parent_[x] != x) {
      parent_[x] = Find(parent_[x]);
    }
    return parent_[x];
  }
};

int64_t Boruvka(int64_t n, int64_t m) {
  Dsu dsu{n};
  int64_t sum = 0;
  int64_t components = n;
  components = n;
  while (components > 1) {
    std::vector<int64_t> min_edge(n + 1, -1);
    for (int64_t i = 0; i < m; ++i) {
      int64_t start = edges[i].start;
      int64_t finish = edges[i].finish;
      int64_t weight = edges[i].weight;
      int64_t root_u = dsu.Find(start);
      int64_t root_v = dsu.Find(finish);

      if (root_u != root_v) {
        if (min_edge[root_u] == -1 || weight < edges[min_edge[root_u]].weight) {
          min_edge[root_u] = i;
        }
        if (min_edge[root_v] == -1 || weight < edges[min_edge[root_v]].weight) {
          min_edge[root_v] = i;
        }
      }
    }

    for (int64_t i = 1; i <= n; ++i) {
      if (min_edge[i] != -1) {
        int64_t idx = min_edge[i];
        int64_t start = edges[idx].start;
        int64_t finish = edges[idx].finish;
        int64_t weight = edges[idx].weight;

        if (dsu.Find(start) != dsu.Find(finish)) {
          dsu.Unite(start, finish, weight);
          sum += edges[idx].weight;
          components--;
        }
      }
    }
  }
  return sum;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int64_t n = 0;
  int64_t m = 0;
  std::cin >> n >> m;
  Dsu dsu{n};
  for (int64_t i = 0; i < m; ++i) {
    int64_t begin = 0;
    int64_t end = 0;
    int64_t weight = 0;
    std::cin >> begin >> end >> weight;
    edges.emplace_back(begin, end, weight);
  }
  std::cout << Boruvka(n, m);
  return 0;
}