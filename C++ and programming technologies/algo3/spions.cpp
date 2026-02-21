#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

class Edge {
 public:
  int one;
  int two;
  int weight;

  explicit Edge(int one, int two, int weight) : one(one), two(two), weight(weight) {
  }
};

class Dsu {
 private:
  std::vector<int> parent_;
  std::vector<int> size_;
  std::vector<int> sum_;

 public:
  explicit Dsu(int n) {
    parent_.resize(n + 1);
    size_.resize(n + 1, 1);
    sum_.resize(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
      parent_[i] = i;
    }
  }

  int Getsum(const int& x) {
    return sum_[Find(x)];
  }

  int Find(const int& x) {
    if (parent_[x] != x) {
      parent_[x] = Find(parent_[x]);
    }
    return parent_[x];
  }

  void Unite(const int& x, const int& y, const int& w) {
    int x_root = Find(x);
    int y_root = Find(y);
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
};

bool Comp(Edge a, Edge b) {
  return a.weight < b.weight;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::vector<Edge> edges;
  int n = 0;
  std::cin >> n;
  Dsu dsu{n};
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      int w = 0;
      std::cin >> w;
      Edge edge = Edge(i, j, w);
      edges.push_back(edge);
    }
  }
  for (int i = 1; i <= n; ++i) {
    int w = 0;
    std::cin >> w;
    Edge edge = Edge(0, i, w);
    edges.push_back(edge);
  }
  std::sort(edges.begin(), edges.end(), Comp);
  for (auto edge : edges) {
    dsu.Unite(edge.one, edge.two, edge.weight);
  }
  std::cout << dsu.Getsum(1);
  return 0;
}