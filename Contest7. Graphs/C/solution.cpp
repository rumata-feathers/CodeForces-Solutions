#include <iostream>
#include <vector>

struct G {
  std::vector<std::vector<int>> g;
  std::vector<int> used;
  std::vector<int> tin, tout;
  int timer = 0;
  std::vector<std::string> color;
  std::vector<int> parent;
  void dfs(int v, int p = -1) {
    tin[v] = timer++;
    parent[v] = p;
    color[v] = "GREY";
    for (int to : g[v]) {
      if (color[to] != "WHITE") continue;
      dfs(to, v);
    }
    tout[v] = timer++;
    color[v] = "BLACK";
  }
  bool is_parent(int v, int p) {
    if ((tin[v] < tin[p]) && (tin[p] < tout[p]) && (tout[p] < tout[v])) {
      return true;
    }
    return false;
  }
  explicit G(int n) {
    g = std::vector<std::vector<int>>(n);
    used = std::vector<int>(n);
    tin = std::vector<int>(n);
    tout = std::vector<int>(n);
    parent = std::vector<int>(n);
    color = std::vector<std::string>(n, "WHITE");
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n;
  std::cin >> n;
  G graph(n);
  int root;
  for (int i = 0; i < n; ++i) {
    int edge;
    std::cin >> edge;
    if (edge != 0) graph.g[edge - 1].push_back(i);
    else root = i;
  }
  graph.dfs(root);
  int requests;
  std::cin >> requests;
  for (int i = 0; i < requests; ++i) {
    int v, u;
    std::cin >> v >> u;
    std::cout << graph.is_parent(--v, --u) << '\n';
  }
  return 0;
}


