#include <iostream>
#include <vector>
#include <deque>
#include <cstdint>
#include <limits>

size_t First(size_t n) {
  return n + 1000;
}

size_t Second(size_t n) {
  return n - 1;
}

size_t Third(size_t n) {
  size_t last = n % 10;
  size_t first = n / 10;
  return last * 1000 + first;
}

size_t Fourth(size_t n) {
  size_t first = n / 1000;
  size_t last = n % 1000;
  return last * 10 + first;
}

std::vector<size_t> Get(size_t n) {
  std::vector<size_t> v;
  if (n / 1000 != 9) {
    v.push_back(First(n));
  }
  if (n % 10 != 1) {
    v.push_back(Second(n));
  }
  v.push_back(Third(n));
  v.push_back(Fourth(n));
  return v;
}

class Graph {
 private:
  std::vector<std::vector<size_t>> adj_list_;

 public:
  explicit Graph() : adj_list_(100000) {
  }

  static std::vector<size_t> BFS(size_t a, size_t b) {
    Graph v;
    std::vector<std::vector<size_t>> dist(100000);
    std::deque<size_t> q;
    q.push_front(a);
    while (!q.empty()) {
      size_t current = q.front();
      v.adj_list_[current] = Get(current);
      for (auto ver : v.adj_list_[current]) {
        if (!dist[ver].empty()) {
          continue;
        }
        dist[ver] = dist[current];
        dist[ver].push_back(ver);
        if (ver == b) {
          return dist[ver];
        }
        q.push_back(ver);
      }
      q.pop_front();
    }
    return dist[a];
  }
};

int main() {
  size_t a = 0;
  size_t b = 0;
  std::cin >> a >> b;
  auto v = Graph::BFS(a, b);
  std::cout << v.size() << "\n";
  std::cout << a << "\n";
  for (auto x : v) {
    std::cout << x << "\n";
  }
  return 0;
}