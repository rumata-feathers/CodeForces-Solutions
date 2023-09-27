#include <iostream>
#include <vector>

bool bit(long long mask, long long pos) {
    return (mask >> pos ) & 1;
}

int main() {

    long long n;
    std::cin >> n;
    std::vector<std::vector<long long>> pin(n, std::vector<long long>(n));
    for (long long i = 0; i < n; ++i) {
        for (long long j = 0; j < n; ++j) {
            std::cin >> pin[i][j];
        }
    }
    std::vector<std::vector<long long>> dp(n, std::vector<long long>(1 << n, 999999999));
    for (long long i = 0; i < n; ++i) {
        dp[i][0] = 0;
        dp[i][1<<i] = 0;
    }
    long long newmask = 0;
    for (long long mask = 1; mask < 1<<n; ++mask) {
        for (long long v = 0; v < n; ++v) {
            if (bit(mask, v)){
                for (long long u = 0; u < n; ++u) {
                    if (!bit(mask, u)) {
                        newmask = mask | (1 << u);
                        dp[u][newmask] = std::min(dp[u][newmask], dp[v][mask] + pin[v][u]);
                    }
                }
            }
        }
    }
    long long result = 99999999999, last = -1;
    for (long long i = 0; i < n; ++i) {
        if (dp[i][(1 << n) - 1] < result) {
            last = i;
            result = dp[i][(1 << n) - 1];
        }
    }
    std::cout << result << '\n';
    std::cout << last + 1 << ' ';
    long long mask = (1<<n) - (1<< last)- 1, i = 0;
    while (mask != 0) {
        if (dp[last][mask + (1<<last)] - dp[i][mask] == pin[last][i]) {
            mask -= (1 << i);
            std::cout << i + 1 << ' ';
            last = i;
            i = 0;
        }else {
            ++i;
        }
    }
    return 0;
}

