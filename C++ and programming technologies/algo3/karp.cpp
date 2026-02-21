#include <iostream>
#include <vector>
#include <climits>
#include <queue>

std::vector<std::vector<int>> graph;

bool Bfs(std::vector<std::vector<int>>& temp, std::vector<int>& parent, int n) {
  std::vector<bool> visited(n + 1, false);
  std::queue<int> q;
  q.push(1);
  visited[1] = true;
  parent[1] = -1;
  while (!q.empty()) {
    int current = q.front();
    q.pop();
    for (int j = 1; j <= n; ++j) {
      if (!visited[j] and temp[current][j]) {
        parent[j] = current;
        if (j == n) {
          return true;
        }
        visited[j] = true;
        q.push(j);
      }
    }
  }
  return false;
}

int Karp(int n) {
  int aristocrat_flow = 0;
  std::vector<std::vector<int>> temp = graph;
  std::vector<int> parent(n + 1);
  while (Bfs(temp, parent, n)) {
    int narrow_passage = INT_MAX;
    int current = n;
    while (current != 1) {
      int begin = parent[current];
      int end = current;
      narrow_passage = std::min(narrow_passage, temp[begin][end]);
      current = parent[current];
    }

    current = n;
    while (current != 1) {
      int begin = parent[current];
      int end = current;
      temp[begin][end] -= narrow_passage;
      temp[end][begin] += narrow_passage;
      current = parent[current];
    }
    aristocrat_flow += narrow_passage;
  }
  return aristocrat_flow;
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  graph.resize(n + 1, std::vector<int>(n + 1, 0));
  for (int i = 0; i < m; ++i) {
    int begin = 0;
    int end = 0;
    int weight = 0;
    std::cin >> begin >> end >> weight;
    graph[begin][end] += weight;
  }

  std::cout << Karp(n);  // запустили карпа
  return 0;
}