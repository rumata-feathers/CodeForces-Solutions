#include <iostream>
#include <vector>

bool bit(size_t mask, int u) {
    if ((mask >> u) & 1) return true;
    return false;
}

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<std::string> input(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> input[i];
    }
    std::vector<size_t> dp(1 << n);
    size_t newmask = 0;
    for (size_t mask = 0; mask < (1<<n); ++mask) {
        for (int v = 0; v < n; ++v) {
            if (bit(mask, v)) {
                for (int u = 0; u < n; ++u) {
                    if (bit(mask, u) && input[v][u] == 'Y') {
                        newmask = (mask ^ (1 << v)) ^ (1 << u);
                        dp[mask] = std::max(dp[mask], dp[newmask] + 2);
                    }
                }
            }
        }
    }
    return 0;
}

