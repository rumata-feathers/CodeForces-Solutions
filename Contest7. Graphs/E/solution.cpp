#include <iostream>
#include <vector>
#include <set>

struct G {
  std::vector<std::vector<int>> g;
  std::vector<std::vector<int>> gr;
  std::vector<int> color;
  std::vector<int> gad;
  std::vector<bool> used;
  void dfs(int v) {
    used[v] = true;
    for (int to : g[v]) {
      if (used[to]) continue;
      dfs(to);
    }
    gad.push_back(v);
  }
  void dfsr(int v, int col) {
    used[v] = true;
    color[v] = col;
    for (int to : gr[v]) {
      if (used[to]) continue;
      dfsr(to, col);
    }
  }
  explicit G(int n) {
    g = std::vector<std::vector<int>>(n);
    gr = std::vector<std::vector<int>>(n);
    color = std::vector<int>(n);
    used = std::vector<bool>(n, false);
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
    --v;
    --u;
    graph.g[v].push_back(u);
    graph.gr[u].push_back(v);
  }
  for (int i = 0; i < n; ++i) {
    if (!graph.used[i]) {
      graph.dfs(i);
    }
  }
  std::reverse(graph.gad.begin(), graph.gad.end());
  graph.used = std::vector<bool>(n, false);
  int counter = 0;
  for (auto& v : graph.gad) {
    if (!graph.used[v]) {
      graph.dfsr(v, counter++);
    }
  }
  std::set<std::pair<int, int>> edges;
  for (int i = 0; i < n; ++i) {
    for (int j : graph.g[i]) {
      if (graph.color[i] != graph.color[j])
        edges.insert({graph.color[i], graph.color[j]});
    }
  }
  std::cout << edges.size();
  return 0;
}


