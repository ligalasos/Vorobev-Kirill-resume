#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

struct Edge {
  int to = 0;
  int rev = 0;
  int capacity = 0;
};

class Dinic {
 public:
  explicit Dinic(int n) : size_(n), graph_(n), level_(n), ptr_(n) {
  }

  void Addedge(int fr, int to, int cap) {
    Edge forward{to, static_cast<int>(graph_[to].size()), cap};
    Edge backward{fr, static_cast<int>(graph_[fr].size()), 0};
    graph_[fr].push_back(forward);
    graph_[to].push_back(backward);
  }

  int Maxflow(int s, int t) {
    int total = 0;
    while (Bfs(s, t)) {
      std::fill(ptr_.begin(), ptr_.end(), 0);
      while (int pushed = Dfs(s, t, std::numeric_limits<int>::max())) {
        total += pushed;
      }
    }
    return total;
  }

 private:
  int size_;
  std::vector<std::vector<Edge>> graph_;
  std::vector<int> level_;
  std::vector<int> ptr_;

  bool Bfs(int s, int t) {
    std::fill(level_.begin(), level_.end(), -1);
    std::queue<int> q;
    level_[s] = 0;
    q.push(s);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      size_++;
      for (const Edge& e : graph_[u]) {
        if (e.capacity > 0 && level_[e.to] == -1) {
          level_[e.to] = level_[u] + 1;
          q.push(e.to);
          if (e.to == t) {
            return true;
          }
        }
      }
    }
    return false;
  }

  int Dfs(int u, int t, int flow) {
    if (u == t) {
      return flow;
    }
    for (int& i = ptr_[u]; i < static_cast<int>(graph_[u].size()); ++i) {
      Edge& e = graph_[u][i];
      if (e.capacity > 0 && level_[e.to] == level_[u] + 1) {
        int pushed = Dfs(e.to, t, std::min(flow, e.capacity));
        if (pushed > 0) {
          e.capacity -= pushed;
          graph_[e.to][e.rev].capacity += pushed;
          return pushed;
        }
      }
    }
    return 0;
  }
};

struct Cell {
  int x = 0;
  int y = 0;
  int valency = 0;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<std::string> grid(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> grid[i];
  }

  const std::unordered_map<char, int> valence{{'H', 1}, {'O', 2}, {'N', 3}, {'C', 4}};

  std::vector<Cell> black;
  std::vector<Cell> white;
  bool has_elements = false;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      const char c = grid[i][j];
      if (c == '.') {
        continue;
      }
      has_elements = true;
      const auto it = valence.find(c);
      if (it == valence.end()) {
        continue;
      }
      const int v = it->second;
      if ((i + j) % 2 == 0) {
        black.push_back({i, j, v});
      } else {
        white.push_back({i, j, v});
      }
    }
  }

  if (!has_elements) {
    std::cout << "Invalid\n";
    return 0;
  }

  int sum_black = 0;
  for (const auto& cell : black) {
    sum_black += cell.valency;
  }

  int sum_white = 0;
  for (const auto& cell : white) {
    sum_white += cell.valency;
  }

  if (sum_black != sum_white) {
    std::cout << "Invalid\n";
    return 0;
  }

  Dinic dinic(static_cast<int>(2 + black.size() + white.size()));

  for (int i = 0; i < static_cast<int>(black.size()); ++i) {
    dinic.Addedge(0, 2 + i, black[i].valency);
  }

  for (int i = 0; i < static_cast<int>(white.size()); ++i) {
    dinic.Addedge(static_cast<int>(2 + black.size() + i), 1, white[i].valency);
  }

  const std::vector<std::pair<int, int>> directions{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  std::map<std::pair<int, int>, int> white_map;

  for (int i = 0; i < static_cast<int>(white.size()); ++i) {
    white_map[{white[i].x, white[i].y}] = i;
  }

  for (int b_idx = 0; b_idx < static_cast<int>(black.size()); ++b_idx) {
    const Cell& b_cell = black[b_idx];
    for (const auto& [dx, dy] : directions) {
      const int nx = b_cell.x + dx;
      const int ny = b_cell.y + dy;
      if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
        const auto it = white_map.find({nx, ny});
        if (it != white_map.end()) {
          const int w_idx = it->second;
          dinic.Addedge(2 + b_idx, static_cast<int>(2 + black.size() + w_idx), 1);
        }
      }
    }
  }

  const int max_flow = dinic.Maxflow(0, 1);
  std::cout << (max_flow == sum_black ? "Valid" : "Invalid") << '\n';

  return 0;
}