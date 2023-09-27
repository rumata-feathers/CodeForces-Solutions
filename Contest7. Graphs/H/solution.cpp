#include <iostream>
#include <vector>

struct G {
  std::vector<std::vector<int>> g;
  std::vector<int> tin;
  std::vector<bool> used;
  std::vector<int> ret;
  std::vector<std::pair<int, int>> bridges;
  int timer = 0;
  void dfs(int v, int p = -1) {
    tin[v] = timer++;
    ret[v] = tin[v];
    used[v] = true;
    for (int to : g[v]) {
      if (to == p) continue;
      if (used[to]) ret[v] = std::min(ret[v], tin[to]);
      else {
        dfs(to, v);
        ret[v] = std::min(ret[v], ret[to]);
        if (ret[to] == tin[to]) {
          bridges.emplace_back(v, to);
        }
      }
    }
  }

  explicit G(int n) {
    g = std::vector<std::vector<int>>(n);
    used = std::vector<bool>(n);
    ret = std::vector<int>(n);
    tin = std::vector<int>(n);
  }
};

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::pair<int, int>> edge;
  G g(n);
  for (int i = 0; i < m; ++i) {
    int v, u;
    std::cin >> v >> u;
    --v;
    --u;
    g.g[v].push_back(u);
    g.g[u].push_back(v);
    edge.emplace_back(v, u);
  }
  for (int i = 0; i < n; ++i) {
    if (!g.used[i]) g.dfs(i);
  }
  std::cout << g.bridges.size() << '\n';
  std::vector<int> res;
  for (int i = 0; i < m; ++i) {
    if (std::find(g.bridges.begin(), g.bridges.end(), edge[i]) != g.bridges.end()
        || std::find(g.bridges.begin(), g.bridges.end(),
                     std::make_pair(edge[i].second,
                                    edge[i].first)) != g.bridges.end()) {
      std::cout << i + 1 << ' ';
    }
  }
  return 0;
}

