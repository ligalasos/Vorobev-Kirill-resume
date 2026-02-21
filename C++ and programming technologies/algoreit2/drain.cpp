#include <iostream>
#include <vector>
#include <queue>

std::vector<std::pair<size_t, size_t>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool BFS(size_t i, size_t j, std::vector<std::vector<size_t>>& grid, std::vector<std::vector<bool>>& visited) {
  std::queue<std::pair<size_t, size_t>> q;
  q.emplace(i, j);
  visited[i][j] = true;
  size_t current_height = grid[i][j];
  bool is_lowest = true;

  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop();
    for (auto [dx, dy] : dirs) {
      size_t nx = x + dx;
      size_t ny = y + dy;
      if (nx < 0 || nx >= grid.size() || ny < 0 || ny >= grid[0].size()) {
        continue;
      }
      if (grid[nx][ny] < current_height) {
        is_lowest = false;
      } else if (grid[nx][ny] == current_height && !visited[nx][ny]) {
        visited[nx][ny] = true;
        q.emplace(nx, ny);
      }
    }
  }
  return is_lowest;
}

int main() {
  size_t n = 0;
  size_t m = 0;
  std::cin >> n >> m;
  std::vector<std::vector<size_t>> grid(n, std::vector<size_t>(m));
  std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      std::cin >> grid[i][j];
    }
  }
  size_t drains = 0;
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < m; ++j) {
      if (visited[i][j]) {
        continue;
      }
      if (BFS(i, j, grid, visited)) {
        drains++;
      }
    }
  }
  std::cout << drains;
  return 0;
}