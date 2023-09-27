#include <iostream>
#include <vector>

int main() {
    size_t n;
    std::cin >> n;
    std::vector<std::vector<size_t>> dp(n + 1, std::vector<size_t>(n + 1, 0));
    std::vector<std::vector<size_t>> pref_sum(n + 1, std::vector<size_t>(n + 1, 0));
    for (size_t i = 1; i < n + 1; ++i) {
        dp[i][i] = 1;
        for (size_t j = 1; j <= n/2; ++j) {
            if (i > j) dp[i][j] = pref_sum[i - j][2*j];
        }
        pref_sum[i][n] = dp[i][n];
        for (size_t j = n - 1; j > 0; --j) {
            pref_sum[i][j] = pref_sum[i][j + 1] + dp[i][j];
        }
    }

    std::cout << pref_sum[n][1];
    return 0;
}

