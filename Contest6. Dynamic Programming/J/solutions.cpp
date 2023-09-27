#include <iostream>
#include <vector>

void print(std::vector<std::vector<size_t>> A) {
    std::cout << "MATRIX:\n";
    for (auto & i : A) {
        for (auto & j: i) {
            std::cout << j << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "-------\n";
}

bool check(size_t mask1, size_t mask2, size_t size) {
    bool a, b, c, d;
    for (size_t i = 0; i < size - 1; ++i) {
        a = ((mask1 >> i)&1);
        b = ((mask1 >> (i + 1))&1);
        c = ((mask2 >> i)&1);
        d = ((mask2 >> (i + 1))&1);
        if (a == b && c == d && a == c) return false;
    }
    return true;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    if (n >= m) std::swap(n, m);
    std::vector<std::vector<size_t>> dp(2, std::vector<size_t>(1 << n));
    for (size_t i = 0; i < (1 << n); ++i) {
        dp[0][i] = 1;
    }
    for (size_t i = 1; i < m; ++i) {
        for (size_t j = 0; j < (1 << n); ++j) {
            dp[i%2][j] = 0;
            for (size_t k = 0; k < (1 << n); ++k) {
                dp[i % 2][j] += dp[(i - 1) % 2][k] * check(k, j, n);
            }
        }
    }
    size_t res = 0;
    for (size_t i = 0; i < (1 << n); ++i) {
        res += dp[(m - 1) % 2][i];
    }
    std::cout << res;
    return 0;
}

