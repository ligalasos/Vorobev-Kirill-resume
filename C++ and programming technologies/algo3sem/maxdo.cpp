#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

class SegmentTree {
 private:
  std::vector<std::pair<int, int>> tree_;
  int len_ = 0;

  void Build(const std::vector<int>& m, int node, int tl, int tr) {
    if (tl == tr) {
      tree_[node] = {m[tl], 1};
      return;
    }
    int tm = (tl + tr) / 2;
    Build(m, 2 * node, tl, tm);
    Build(m, 2 * node + 1, tm + 1, tr);
    if ()
  }

  int Minimum(int node, int tl, int tr, int left, int right) {
    if (tl > right || tr < left) {
      return INT_MAX;
    }
    if (left <= tl && tr <= right) {
      return tree_[node];
    }
    int tm = (tl + tr) / 2;
    return std::min(Minimum(2 * node, tl, tm, left, right), Minimum(2 * node + 1, tm + 1, tr, left, right));
  }

 public:
  explicit SegmentTree(const std::vector<int>& m) {
    len_ = static_cast<int>(m.size());
    tree_.resize(4 * len_);
    Build(m, 1, 0, len_ - 1);
  }
  int Rmq(int l, int r) {
    if (l < 0 || r >= len_ || l > r) {
      return INT_MAX;
    }
    return Minimum(1, 0, len_ - 1, l, r);
  }
};

int main() {
  int n = 0;
  int k = 0;
  std::cin >> n >> k;
  std::vector<int> m(n);
  for (int i = 0; i < n; i++) {
    std::cin >> m[i];
  }
  SegmentTree tree(m);
  for (int i = 0; i < k; ++i) {
    int l = 0;
    int r = 0;
    std::cin >> l >> r;
    --l;
    --r;
    std::cout << tree.Rmq(l, r) << "\n";
  }
  return 0;
}