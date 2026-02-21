#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <numeric>
#include <string>

class SegmentTree {
 private:
  std::vector<int64_t> tree_;
  int64_t len_ = 0;

  void Build(const std::vector<int64_t>& m, int64_t node, int64_t tl, int64_t tr) {
    if (tl == tr) {
      tree_[node] = m[tl];
      return;
    }
    int64_t tm = (tl + tr) / 2;
    Build(m, 2 * node, tl, tm);
    Build(m, 2 * node + 1, tm + 1, tr);
    tree_[node] = tree_[2 * node] + tree_[2 * node + 1];
  }

  int64_t GetSum(int64_t node, int64_t tl, int64_t tr, int64_t l, int64_t r) {
    if (l > r) {
      return 0;
    }
    if (l == tl && r == tr) {
      return tree_[node];
    }
    int64_t tm = (tl + tr) / 2;
    return GetSum(2 * node, tl, tm, l, std::min(r, tm)) + GetSum(2 * node + 1, tm + 1, tr, std::max(l, tm + 1), r);
  }

  void Update(int64_t node, int64_t tl, int64_t tr, int64_t pos, int64_t new_val) {
    if (tl == tr) {
      tree_[node] = new_val;
      return;
    }
    int64_t tm = (tl + tr) / 2;
    if (pos <= tm) {
      Update(2 * node, tl, tm, pos, new_val);
    } else {
      Update(2 * node + 1, tm + 1, tr, pos, new_val);
    }
    tree_[node] = tree_[2 * node] + tree_[2 * node + 1];
  }

 public:
  explicit SegmentTree(const std::vector<int64_t>& m) {
    len_ = static_cast<int64_t>(m.size());
    tree_.resize(4 * len_);
    Build(m, 1, 0, len_ - 1);
  }

  int64_t Sum(int64_t l, int64_t r) {
    if (l < 0 || r >= len_ || l > r) {
      return 0;
    }
    return GetSum(1, 0, len_ - 1, l, r);
  }

  void Up(int64_t pos, int64_t new_val) {
    Update(1, 0, len_ - 1, pos, new_val);
  }
};

int main() {
  int64_t n = 0;
  int64_t k = 0;
  std::cin >> n;
  std::vector<int64_t> m(n);
  for (int64_t i = 0; i < n; i++) {
    std::cin >> m[i];
  }
  std::cin >> k;
  SegmentTree tree(m);
  std::vector<int64_t> results;

  for (int64_t i = 0; i < k; ++i) {
    std::string command;
    std::cin >> command;
    if (command == "s") {
      int64_t l = 0;
      int64_t r = 0;
      std::cin >> l >> r;
      l--;
      r--;
      results.push_back(tree.Sum(l, r));
    } else if (command == "u") {
      int64_t pos = 0;
      int64_t x = 0;
      std::cin >> pos >> x;
      pos--;
      tree.Up(pos, x);
      m[pos] = x;
    }
  }

  for (size_t i = 0; i < results.size(); i++) {
    std::cout << results[i];
    if (i != results.size() - 1) {
      std::cout << " ";
    }
  }
  std::cout << std::endl;

  return 0;
}