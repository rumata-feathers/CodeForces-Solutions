#include <iostream>
#include <vector>

struct G {
  std::vector<std::vector<int>> g;
  std::vector<std::pair<int, int>> tout;
  int timer = 0;
  bool has_loop = false;
  std::vector<std::string> color;
  void dfs(int v) {
    timer++;
    color[v] = "GREY";
    for (int to : g[v]) {
      if (color[to] == "GREY") has_loop = true;
      if (color[to] != "WHITE") continue;
      dfs(to);
    }
    tout[v] = {timer++, v};
    color[v] = "BLACK";
  }
  explicit G(int n) {
    g = std::vector<std::vector<int>>(n);
    tout = std::vector<std::pair<int, int>>(n);
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
  }
  for (int i = 0; i < n; ++i) {
    if (graph.color[i] == "WHITE")
      graph.dfs(i);
    if (graph.has_loop){
      std::cout << -1;
      return 0;
    }
  }
  std::sort(graph.tout.rbegin(), graph.tout.rend());
  for (auto i: graph.tout) {
    std::cout << i.second + 1 << ' ';
  }
  return 0;
}


