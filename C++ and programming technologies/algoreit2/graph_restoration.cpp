#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <deque>

std::vector<std::vector<std::pair<int, int>>> graph;
std::vector<std::string> color;
std::vector<std::pair<std::string, int>> x;

void DFS(int current) {
  color[current] = "grey";
  for (const auto a : graph[current]) {
    int ver = a.first;
    int weight = a.second;
    if (color[ver] == "white") {
      std::string sign_current = x[current].first;
      int k_current = x[current].second;
      if (sign_current == "-") {
        x[ver].first = "+";
        x[ver].first = weight - x[current].second;
      } else {
        x[ver].first = "-";
        x[ver].first = weight - x[current].second;
      }
      DFS(ver);
    }
  }
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  graph.resize(n + 1);
  color.resize(n + 1, "white");
  x.resize(n + 1);
  x[1] = {"+", 0};
  for (int i = 0; i < m; ++i) {
    int begin = 0;
    int end = 0;
    int weight = 0;
    std::cin >> begin >> end >> weight;
    graph[begin].emplace_back(end, weight);
    graph[end].emplace_back(begin, weight);
  }
  DFS(1);
  int xxx = 0;
  int this_one = 0;
  int min_x = 0;
  int max_x = 0;
  int this_one_min = 0;
  int this_one_max = 0;
  for (int i = 1; i <= n; ++i) {
    if (x[i].first == "-") {
      if (this_one_max < x[i].second) {
        max_x = i;
      }
      this_one_max = std::max(x[i].second, this_one_max);
    } else {
      if (x[i].second < this_one_min) {
        min_x = i;
      }
      this_one_min = std::min(x[i].second, this_one_min);
    }
  }
  if (-this_one_min > this_one_max) {
    this_one = this_one_min;
    xxx = min_x;
  } else {
    this_one = this_one_max;
    xxx = max_x;
  }
  
  return 0;
}