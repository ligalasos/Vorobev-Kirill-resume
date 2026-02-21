#include <iostream>
#include <vector>
#include <queue>
#include <deque>

struct Vertex {
    int num;
    std::vector<std::pair<int, int>> neighbours;
    Vertex(int n) : num(n) {} // Добавлен конструктор
};

class Graph {
private:
    std::vector<Vertex> adj_list_;

public:
    Graph(const std::vector<std::vector<int>>& in, int n) {
        adj_list_.reserve(n);
        for (int i = 0; i < n; ++i) {
            adj_list_.emplace_back(i);
        }
        for (const auto& edge : in) {
            int a = edge[0];
            int b = edge[1];
            int w = edge[2];
            adj_list_[a].neighbours.emplace_back(b, w);
            adj_list_[b].neighbours.emplace_back(a, w);
        }
    }

    std::vector<int> bfs(int start = 0) {
        int n = adj_list_.size();
        std::vector<bool> used(n, false);
        std::deque<int> deque;
        std::vector<int> dist(n, -1);

        deque.push_back(start);
        dist[start] = 0;
        used[start] = true;

        while (!deque.empty()) {
            int current = deque.front();
            deque.pop_front();
            
            for (const auto& [neigh, w] : adj_list_[current].neighbours) {
                if (!used[neigh]) {
                    dist[neigh] = dist[current] + w;
                    used[neigh] = true;
                    if (w) {
                      deque.push_back(neigh);
                    } else {
                      deque.push_front(neigh);
                    }

                }
            }
        }
        return dist;
    }
};

int main() {
    int v, e;
    std::cin >> v >> e;

    std::vector<std::vector<int>> input(e, std::vector<int>(3));
    for (int i = 0; i < e; ++i) {
        std::cin >> input[i][0] >> input[i][1];
        input[i][2] = 1; // Все веса равны 1
    }

    Graph graph(input, v);
    std::vector<int> distances = graph.bfs(0);

    std::cout << "Расстояния от вершины 0:\n";
    for (int i = 0; i < v; ++i) {
        std::cout << "Вершина " << i << ": " << distances[i] << "\n";
    }

    return 0;
}
