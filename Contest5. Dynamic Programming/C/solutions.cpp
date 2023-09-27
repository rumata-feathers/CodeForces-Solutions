#include <iostream>
#include <vector>
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<int> vil(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> vil[i];
    }
    long long ans;
    std::vector<std::vector<long long> > dp(n + 1, std::vector<long long>(m + 1, 0));
    for (int i = 2; i < n + 1; ++i) {
        for (int j = 1; (j < m + 1) && (j < i); ++j) {
            if (j == 1) dp[i][j] = dp[i-1][j] + (vil[i-1] - vil[i-2])*(i-1);
            else {
                dp[i][j] = dp[i - 1][j-1];
                for (int k = i - 1; k > 0; --k) {
                    ans = dp[k][j - 1];
                    for (int l = k + 1; l < i; ++l) {
                        ans += std::min(vil[l - 1] - vil[k - 1], vil[i - 1] - vil[l - 1]);
                    }
                    dp[i][j] = std::min(dp[i][j], ans);
                }
            }
        }
    }
    std::vector<int> answer;
    long long result, count;
    int last = n;
    int cur_l;
    for (int k = m; k > 0; --k) {
        result = dp[last][k];
        cur_l = last;
        for (int i = last - 1; i > 0; --i) {
            count = dp[i][k];
            for (int j = i + 1; j <= last; ++j) {
                if (last != n) count += std::min(vil[j - 1] - vil[i - 1], vil[last] - vil[j-1]);
                else count += vil[j - 1] - vil[i - 1];
            }
            if (count < result) {
                cur_l = i;
                result = count;
            }
        }
        if (k == m) std::cout << result << '\n';
        last = cur_l;
        answer.push_back(vil[last-1]);
        --last;
    }
    std::reverse(answer.begin(), answer.end());
    for (int i = 0; i < m; ++i) {
        std::cout << answer[i] << ' ';
    }
    return 0;
}

