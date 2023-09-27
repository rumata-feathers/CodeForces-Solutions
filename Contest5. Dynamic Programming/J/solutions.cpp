#include <iostream>
#include <vector>

int main() {
    long long c = 1000000007;
    int n, max_el;
    std::cin >> n;
    std::vector<int> a(n);
    max_el = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        max_el = std::max(a[i], max_el);
    }
    std::vector<int> count(max_el + 1);
    std::vector<long long> dp(n + 1);
    int prev = 0;
    for (int i = 1; i < n + 1; ++i) {
        dp[i] = 2*dp[i-1] + 1;
        prev = count[a[i - 1]];
        count[a[i - 1]] = i;
        if (prev != 0) dp[i] -= dp[prev - 1] + 1;
        dp[i] += c;
        dp[i] %= c;
    }
    std::cout << dp[n] % (c);
    return 0;
}

