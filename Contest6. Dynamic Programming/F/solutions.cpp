#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n, m;
  std::cin >> n >> m;
  std::vector<int> travel_cost(n);
  std::vector<std::vector<int>> prices(n, std::vector<int>(m));
  for (int i = 0; i < n; ++i) {
    std::cin >> travel_cost[i];
    for (int j = 0; j < m; ++j) {
      std::cin >> prices[i][j];
    }
  }

  std::vector<std::vector<std::vector<int>>> dp(2, std::vector<std::vector<int>>((1 << m), std::vector<int>(2)));
  for (int i = 0; i < n+1; ++i) {
    for (int mask = 0; mask < 1 << m; ++mask) {
      for (int k = 0; k < 2; ++k) {
        dp[i%2][mask][k] = 1000000000;
      }
    }
  }
  dp[0][0][0] = 0;
  int result = 1000000000;
  for (int i = 1; i < n + 1; ++i) {
    for (int j = 0; j < 1 << m; ++j) {
      dp[i%2][j][0] = 1000000000;
      dp[i%2][j][1] = 1000000000;
    }
    for (int mask = 0; mask < 1 << m; ++mask) {
      for (int k = 0; k < 2; ++k) {
        dp[i%2][mask][0] = std::min(dp[i%2][mask][0], dp[(i + 1)%2][mask][k]);
        for (int j = 0; j < m; ++j) {
          if ((mask & 1<<j) != 0) {
            int cost = prices[i - 1][j];
            if (k == 0) cost += travel_cost[i - 1];
            dp[i%2][mask][1] = std::min(dp[i%2][mask][1], dp[i%2][mask - (1<<j)][k] + cost);
          }
        }
        if (mask == ((1 << m) - 1)) result = std::min(result, dp[i%2][(1 << m) - 1][k]);
      }
    }
  }
  std::cout << result;
  return 0;
}

