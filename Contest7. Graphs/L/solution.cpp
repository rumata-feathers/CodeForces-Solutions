#include <iostream>
#include <vector>

struct G {
  std::vector<std::vector<long long>> g;
  std::vector<long long> cc;
  std::vector<std::string> color;
  void dfs(long long v) {
    color[v] = "GREY";
    for (long long to : g[v]) {
      if (color[to] != "WHITE") continue;
      cc[to] = cc[v];
      dfs(to);
    }
    color[v] = "BLACK";
  }
  explicit G(long long n) {
    g = std::vector<std::vector<long long>>(n);
    cc = std::vector<long long>(n, -1);
    color = std::vector<std::string>(n, "WHITE");
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  long long n, m;
  std::cin >> n >> m;
  G g(2 * m);
  std::vector<bool> lamps(n);
  std::vector<std::vector<long long>> switches(n);
  for (long long i = 0; i < n; ++i) {
    bool lamp;
    std::cin >> lamp;
    lamps[i] = lamp;
  }
  for (long long i = 0; i < m; ++i) {
    long long amount;
    std::cin >> amount;
    for (long long j = 0; j < amount; ++j) {
      long long lamp;
      std::cin >> lamp;
      switches[--lamp].push_back(i);
    }
  }
  for (long long i = 0; i < n; ++i) {
    long long u = 2*switches[i][0];
    long long v = 2*switches[i][1];
    if (lamps[i]) {
      g.g[u].push_back(v);
      g.g[v].push_back(u);

      g.g[u + 1].push_back(v + 1);
      g.g[v + 1].push_back(u + 1);
    }else{
      g.g[u].push_back(v + 1);
      g.g[v + 1].push_back(u);

      g.g[u + 1].push_back(v);
      g.g[v].push_back(u + 1);
    }
  }
  long long counter = 1;
  for (long long i = 0; i < 2*m; ++i) {
    if (g.color[i] == "WHITE") {
      g.cc[i] = counter++;
      g.dfs(i);
    }
  }
  for (long long i = 0; i < m; ++i) {
    if (g.cc[2*i] == g.cc[2*i + 1]){
      std::cout << "NO";
      return 0;
    }
  }
  std::cout << "YES";
  return 0;
}


