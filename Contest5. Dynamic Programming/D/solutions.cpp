#include <iostream>
#include <vector>

int main() {
    size_t n, k;
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::cin >> n >> k;
    if (n == 1) {
        std::cout << 0;
        return 0;
    }
    if (k == 1) {
        std::cout << n - 1;
        return 0;
    }
    if (k == 0) {
        std::cout << -1;
        return 0;
    }
    size_t p = 0;
    for (size_t i = 1; i < n; i *= 2) ++p;
    if (k >= p) {
        std::cout << p;
        return 0;
    }
    int max_try = 450;
    int c = max_try;
    std::vector<std::vector<size_t>> dp(max_try, std::vector<size_t>(k+1, 1));
    for (size_t i = 0; i < max_try; ++i) {
        dp[i][1] = i + 1;
    }
    for (size_t i = 1; i < max_try; ++i) {
        for (size_t j = 2; j < k + 1; ++j) {
            if (j == 1) dp[i%c][1] = i+1;
            else dp[i%c][j] = dp[(i - 1)%c][j - 1] + dp[(i - 1)%c][j];
            if (dp[i%c][j] >= n){
                std::cout << i;
                return 0;
            }
        }
    }
    return 0;
}

