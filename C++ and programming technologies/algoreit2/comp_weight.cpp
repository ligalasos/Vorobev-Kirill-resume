#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

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
      sum_[x_root] += w;
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

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Dsu dsu{n};
  for (int i = 0; i < m; ++i) {
    int operation = 0;
    std::cin >> operation;
    if (operation == 1) {
      int x = 0;
      int y = 0;
      int w = 0;
      std::cin >> x >> y >> w;
      dsu.Unite(x, y, w);
    }
    if (operation == 2) {
      int x = 0;
      std::cin >> x;
      std::cout << dsu.Getsum(x) << "\n";
    }
  }
  return 0;
}