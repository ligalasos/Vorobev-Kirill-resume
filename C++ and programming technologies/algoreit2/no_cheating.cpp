#include <iostream>
#include <vector>
#include <string>
#include <deque>

class Graph {
 public:
  std::vector<std::vector<size_t>> adj_list_;
  std::vector<std::string> color;

  explicit Graph(size_t n) : adj_list_(n + 1), color(n + 1, "white") {
  }
};

bool Bipartite(Graph& v) {
  std::deque<size_t> d;
  for (size_t i = 1; i < v.color.size(); ++i) {
    if (v.color[i] == "white") {
      v.color[i] = "red";
      d.push_front(i);
      while (!d.empty()) {
        size_t current = d.front();

        for (auto ver : v.adj_list_[current]) {
          if (v.color[current] == "red" and v.color[ver] != "red") {
            if (v.color[ver] == "white") {
              v.color[ver] = "black";
              d.push_back(ver);
            }
            continue;
          }
          if (v.color[current] == "black" and v.color[ver] != "black") {
            if (v.color[ver] == "white") {
              v.color[ver] = "red";
              d.push_back(ver);
            }
            continue;
          }
          return false;
        }
        d.pop_front();
      }
    }
  }
  return true;
}

int main() {
  size_t n = 0;
  size_t m = 0;
  std::cin >> n >> m;
  Graph v(n);
  for (size_t i = 0; i < m; ++i) {
    size_t begin = 0;
    size_t end = 0;
    std::cin >> begin >> end;
    v.adj_list_[begin].push_back(end);
    v.adj_list_[end].push_back(begin);
  }

  if (Bipartite(v)) {
    std::cout << "YES"
              << "\n";
  } else {
    std::cout << "NO"
              << "\n";
  }

  return 0;
}