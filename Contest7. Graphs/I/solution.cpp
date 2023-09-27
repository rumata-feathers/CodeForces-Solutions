#include <iostream>
#include <vector>
#include <set>

struct G {
  std::vector<std::vector<int>> g;
  std::vector<int> tin;
  std::vector<bool> used;
  std::vector<int> ret;
  std::set<int> cp;
  int timer = 0;
  void dfs(int v, int p = -1) {
    tin[v] = timer++;
    ret[v] = tin[v];
    used[v] = true;
    int childs = 0;
    for (int to : g[v]) {
      if (to == p) continue;
      if (used[to]) ret[v] = std::min(ret[v], tin[to]);
      else {
        dfs(to, v);
        ret[v] = std::min(ret[v], ret[to]);
        if (ret[to] >= tin[v] && p != -1)
          cp.insert(v);
        ++childs;
      }
    }
    if (p == -1 && childs >= 2) {
      cp.insert(v);
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
  G g(n);
  for (int i = 0; i < m; ++i) {
    int v, u;
    std::cin >> v >> u;
    --v;
    --u;
    g.g[v].push_back(u);
    g.g[u].push_back(v);
  }
  for (int i = 0; i < n; ++i) {
    if (!g.used[i]) g.dfs(i);
  }
  std::cout << g.cp.size() << '\n';
  for (int v: g.cp) {
    std::cout << v + 1 << ' ';
  }
  return 0;
}

