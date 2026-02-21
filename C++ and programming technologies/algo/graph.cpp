#include <iostream>
#include <vector>

class Graph {
 private:
  int numVertices;
  std::vector<std::vector<int>> adj_list_;
 public:
  Graph(int vertices, bool directed = false) : numVertices(vertices) {
    adj_list_.resize(numVertices);
  }
};

int main() {

  return 0;
}