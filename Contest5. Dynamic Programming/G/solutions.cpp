#include <iostream>
#include <vector>

int main() {
    int n, m;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    std::cin >> m;
    std::vector<int> b(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> b[i];
    }
    std::vector<std::vector<int>> dp;
    for (int i = 0; i < n + 1; ++i) {
        dp.emplace_back(m + 1);
        for (int j = 0; j < m + 1; ++j) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else{
                if (a[i - 1] == b[j - 1]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                } else {
                    dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
    }
    std::cout << dp[n][m];
    return 0;
}

