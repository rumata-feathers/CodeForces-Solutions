#include <iostream>
#include <vector>

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n + 1), b(m + 1);
    std::vector<std::vector<int>> dp;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 0; i < m; ++i) {
        std::cin >> b[i];
    }
    int ideal;
    for (int i = 0; i < n + 1; ++i) {
        dp.emplace_back(m + 1);
        ideal = 0;
        for (int j = 0; j < m + 1; ++j) {
            if (i != 0 && j != 0) {
                dp[i][j] = dp[i-1][j];
                if (a[i - 1] == b[j - 1] && dp[i - 1][j] < ideal + 1) {
                    dp[i][j] = ideal + 1;
                }
                if(a[i - 1] > b[j - 1] && dp[i-1][j] > ideal) {
                    ideal = dp[i-1][j];
                }
            }
        }
    }
    int p = 0;
    for (int i = 0; i < m + 1; ++i) {
        if (dp[n][i] > dp[n][p]) p = i;
    }
    std::cout << dp[n][p];
    return 0;
}

