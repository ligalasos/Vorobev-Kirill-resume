#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

void BFS(int n, int m, std::vector<std::vector<int>>& dist, std::deque<std::pair<int, int>>& q) {
  while (!q.empty()) {
    auto current = q.front();
    auto y = current.first;
    auto x = current.second;
    for (int i = 1; i <= 4; ++i) {
      if (i == 1 and x != 0) {
        if (dist[y][x - 1] != -1) {
          continue;
        }
        dist[y][x - 1] = dist[y][x] + 1;
        q.emplace_back(y, x - 1);
      } else if (i == 2 and x != m - 1) {
        if (dist[y][x + 1] != -1) {
          continue;
        }
        dist[y][x + 1] = dist[y][x] + 1;
        q.emplace_back(y, x + 1);
      } else if (i == 3 and y != 0) {
        if (dist[y - 1][x] != -1) {
          continue;
        }
        dist[y - 1][x] = dist[y][x] + 1;
        q.emplace_back(y - 1, x);
      } else if (i == 4 and y != n - 1) {
        if (dist[y + 1][x] != -1) {
          continue;
        }
        dist[y + 1][x] = dist[y][x] + 1;
        q.emplace_back(y + 1, x);
      }
    }
    q.pop_front();
  }
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<std::vector<int>> v(n, std::vector<int>(m));
  std::vector<std::vector<int>> dist(n, std::vector<int>(m, -1));
  std::deque<std::pair<int, int>> q;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cin >> v[i][j];
      if (v[i][j] == 1) {
        dist[i][j] = 0;
        q.emplace_back(i, j);
      }
    }
  }
  BFS(n, m, dist, q);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      std::cout << dist[i][j] << " ";
    }
    std::cout << "\n";
  }
  return 0;
}