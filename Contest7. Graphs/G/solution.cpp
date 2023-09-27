#include <iostream>
#include <vector>

struct G {
  std::vector<std::vector<int>> g;
  std::vector<int> cc;
  std::vector<std::string> color;
  void dfs(int v) {
    color[v] = "GREY";
    for (int to : g[v]) {
      if (color[to] != "WHITE") continue;
      cc[to] = cc[v];
      dfs(to);
    }
    color[v] = "BLACK";
  }
  explicit G(int n) {
    g = std::vector<std::vector<int>>(n);
    cc = std::vector<int>(n, -1);
    color = std::vector<std::string>(n, "WHITE");
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n, m;
  std::cin >> n >> m;
  G graph(n);
  for (int i = 0; i < m; ++i) {
    int v, u;
    std::cin >> v >> u;
    --v;--u;
    graph.g[v].push_back(u);
    graph.g[u].push_back(v);
  }
  int counter = 1;
  for (int i = 0; i < n; ++i) {
    if (graph.color[i] == "WHITE") {
      graph.cc[i] = counter++;
      graph.dfs(i);
    }
  }
  std::cout << counter - 1<< '\n';
  for (int v:graph.cc) {
    std::cout << v << ' ';
  }
  return 0;
}


