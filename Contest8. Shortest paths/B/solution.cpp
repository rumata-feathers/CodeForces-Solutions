#include <iostream>
#include <vector>
#include <queue>

struct edge {
  int to;
  int cost;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<edge>> g(n);
  for (int i = 0; i < m; ++i) {
    int a, b, c;
    std::cin >> a >> b >> c;
    g[--a].push_back(edge{--b, c});
    g[b].push_back(edge{a, c});
  }
  int ans = 10e7;
  std::vector<std::queue<int>> q(10 * n);
  for (int v = 0; v < n; ++v) {
    for (int i = 0; i < g[v].size(); ++i) {
      //removing edge
      auto v_edge = g[v][i];
      std::swap(g[v][i], g[v][g[v].size() - 1]);
      g[v].pop_back();

      int u = v_edge.to;
      int cost = v_edge.cost;
      std::vector<bool> used(n, false);
      std::vector<int> dist(n, 1e7);

      dist[v] = 0;
      q[0].push(v);
      bool found = false;

      for (int k = 0; k < n*10; ++k) {
        if (found == true) break;
        if (k  + 2 > ans) break;
        while (!q[k].empty()) {
          int x = q[k].front();
          q[k].pop();
          if (x == u) {
            found = true;
            ans = std::min(ans, cost + dist[u]);
            break;
          }
          if (used[x]) continue;
          used[x] = true;
          for (auto& g_edge : g[x]) {
            if (dist[g_edge.to] > dist[x] + g_edge.cost) {
              dist[g_edge.to] = dist[x] + g_edge.cost;
              q[dist[g_edge.to]].push(g_edge.to);
            }
          }
        }
      }

      //add edge back
      g[v].push_back(v_edge);
      std::swap(g[v][i], g[v][g[v].size() - 1]);
    }
  }
  std::cout << ans;
  return 0;
}

