#include <iostream>
#include <deque>
#include <vector>
#include <climits>
#include <cstdint>

class Graph {
 public:
  std::vector<std::vector<std::pair<int, int>>> v;
  explicit Graph(int n) : v(n + 1) {
  }
};

int BFS(int n, Graph& v, int begin, int end) {
  std::vector<int> dist(n + 1, INT_MAX);
  std::deque<int> q;
  dist[begin] = 0;
  q.push_front(begin);
  while (!q.empty()) {
    auto current = q.front();
    q.pop_front();
    for (auto ver : v.v[current]) {
      auto num = ver.first;
      auto weight = ver.second;
      if (dist[num] > dist[current] + weight) {
        if (weight == 0) {
          dist[num] = dist[current] + weight;
          q.push_front(num);
        } else {
          dist[num] = dist[current] + weight;
          q.push_back(num);
        }
      }
    }
  }
  if (dist[end] == INT_MAX) {
    return -1;
  }
  return dist[end];
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Graph v(n);
  for (int i = 0; i < m; ++i) {
    int begin = 0;
    int end = 0;
    std::cin >> begin >> end;
    v.v[begin].emplace_back(end, 0);
    v.v[end].emplace_back(begin, 1);
  }
  int ques = 0;
  std::cin >> ques;
  for (int i = 0; i < ques; ++i) {
    int begin = 0;
    int end = 0;
    std::cin >> begin >> end;
    std::cout << BFS(n, v, begin, end) << "\n";
  }
  return 0;
}


