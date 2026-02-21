#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <deque>
#include <algorithm>

std::vector<std::vector<int>> graph;
std::vector<std::string> color;
std::vector<std::pair<int, int>> bridges;
std::vector<int> time_in;
std::vector<int> time_up;
std::vector<std::string> colors;

void DFS(int current, int& time, int parent = -1) {
  color[current] = "grey";
  time_in[current] = ++time;
  time_up[current] = time;
  for (auto ver : graph[current]) {
    if (ver == parent) {
      continue;
    }
    if (color[ver] == "grey") {
      time_up[current] = std::min(time_in[ver], time_up[current]);
    }
    if (color[ver] == "white") {
      DFS(ver, time, current);
      time_up[current] = std::min(time_up[current], time_up[ver]);
      if (time_in[current] < time_up[ver]) {
        bridges.emplace_back(current, ver);
      }
    }
  }
  color[current] = "black";
}

void BFS(int begin, std::unordered_map<int, int>& comp, int& id) {
  std::deque<int> q;
  q.push_back(begin);
  while (!q.empty()) {
    int current = q.front();
    colors[current] = "white";
    comp[current] = id;
    q.pop_front();
    for (auto ver : graph[current]) {
      if (colors[ver] == "white") {
        continue;
      }
      bool is_bridge = std::find(bridges.begin(), bridges.end(), std::make_pair(current, ver)) != bridges.end() ||
                       std::find(bridges.begin(), bridges.end(), std::make_pair(ver, current)) != bridges.end();
      if (!is_bridge) {
        q.push_back(ver);
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n = 0;
  int m = 0;
  int time = -1;
  std::cin >> n >> m;
  graph.resize(n + 1);
  time_in.resize(n + 1);
  time_up.resize(n + 1);
  color.resize(n + 1, "white");
  for (int i = 0; i < m; ++i) {
    int begin = 0;
    int end = 0;
    std::cin >> begin >> end;
    graph[begin].push_back(end);
    graph[end].push_back(begin);
  }
  DFS(1, time);
  time_in.clear();
  time_in.shrink_to_fit();
  time_up.clear();
  time_up.shrink_to_fit();
  color.clear();
  color.shrink_to_fit();
  colors.resize(n + 1, "black");
  std::unordered_map<int, int> comp;
  int id = 0;
  for (int i = 1; i <= n; ++i) {
    if (colors[i] == "white") {
      continue;
    }
    ++id;
    BFS(i, comp, id);
  }
  std::vector<std::vector<int>> con_graph(id + 1);
  for (auto bridge : bridges) {
    int begin = comp[bridge.first];
    int end = comp[bridge.second];
    con_graph[end].push_back(begin);
    con_graph[begin].push_back(end);
  }
  size_t leaf = 0;
  for (auto k : con_graph) {
    if (k.size() == 1) {
      ++leaf;
    }
  }
  std::cout << (leaf + 1) / 2;
  return 0;
}