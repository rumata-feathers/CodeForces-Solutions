#include <iostream>
#include <vector>
#include <queue>
#include <set>

struct edge{
  int from, to;
  bool wood = false;
  edge(int v, int u, bool flag = false): to(u), from(v), wood(flag) {};
};

struct G {
  std::vector<edge> edges;
  std::vector<std::vector<int>> g;
  std::vector<std::set<int>> components;
  std::queue<int> q;
  std::vector<int> tin;
  std::vector<bool> used;
  std::vector<int> ret;
  int timer = 0;
  void dfs(int v, int p = -1) {
    tin[v] = timer++;
    ret[v] = tin[v];
    used[v] = true;
    for (int num : g[v]) {
      int to;
      if (edges[num].from == v) to = edges[num].to;
      else to = edges[num].from;
      if (to == p) continue;
      if (used[to]) {
        edges[num].from = v;
        edges[num].to = to;
        ret[v] = std::min(ret[v], tin[to]);
      }
      else {
        edges[num].wood = true;
        edges[num].from = v;
        edges[num].to = to;
        dfs(to, v);
        ret[v] = std::min(ret[v], ret[to]);
      }
    }
  }
  bool ret_check(edge& ed) {
    return ret[ed.to] >= tin[ed.from];
  }
  void solution(){
    for(int v = 0; v < g.size(); v++){
      if (!used[v]){
        used[v] = true;
        for (auto ed: g[v]) {
          if (edges[ed].wood) q.push(ed);
        }
      }
      while (!q.empty()) {
        int new_edge = q.front();
        q.pop();
        components.emplace_back();
        components[components.size()-1].insert(new_edge);
        new_dfs(edges[new_edge].to, components.size() -1, edges[new_edge].from);
      }
    }
  }
  void new_dfs(int v, int num, int p = -1) {
    used[v] = true;
    for (auto& ed : g[v]) {
      int to = edges[ed].to;
      if (!used[to] && edges[ed].wood){
        if (!ret_check(edges[ed])) {
          components[num].insert(ed);
          new_dfs(to, num, v);
        } else {
          q.push(ed);
        }
      }else if (used[to])  components[num].insert(ed);
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
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n, m;
  std::cin >> n >> m;
  G g(n);
  for (int i = 0; i < m; ++i) {
    int v, u;
    std::cin >> v >> u;
    g.edges.emplace_back(v, u);
    g.g[v].push_back(i);
    g.g[u].push_back(i);
  }
  for (int i = 0; i < n; ++i) {
    if (!g.used[i]) g.dfs(i);
  }
  std::queue<edge> q;
  std::vector<std::vector<edge>> blocks;
  g.used = std::vector<bool>(n, false);
  g.solution();
  std::cout << g.components.size() << '\n';
  for (auto & component : g.components) {
    std::cout << component.size() << ' ';
    for (auto& i: component) std::cout << i << ' ';
    std::cout << '\n';
  }
  return 0;
}
