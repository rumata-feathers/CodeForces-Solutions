#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<bool>> graph(n, std::vector<bool>(m));
  for (int i = 0; i < m; ++i) {
    int v, u;
    std::cin >> v >> u;
    --v;--u;
    graph[v][i] = true;
    graph[u][i] = true;
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cout << graph[i][j] << ' ';
    }
    std::cout << "\n";
  }
  return 0;
}

