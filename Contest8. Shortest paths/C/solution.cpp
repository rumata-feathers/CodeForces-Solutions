#include <iostream>
#include <vector>

struct graph {
  std::vector<std::vector<int>> g;
  auto do_floyd() {
    for (int k = 0; k < g.size(); ++k) {
      for (int i = 0; i < g.size(); ++i) {
        for (int j = 0; j < g.size(); ++j) {
          g[i][j] = std::min(g[i][j], g[i][k] + g[k][j]);
        }
      }
    }
  }
  explicit graph(int n) {
    g = std::vector<std::vector<int>>(n, std::vector<int>(n));
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  
  int n;
  std::cin >> n;
  graph floyd_graph(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> floyd_graph.g[i][j];
    }
  }
  floyd_graph.do_floyd();
  for (auto& row : floyd_graph.g) {
    for (auto path : row) {
      std::cout << path << ' ';
    }
    std::cout << '\n';
  }
  return 0;
}

