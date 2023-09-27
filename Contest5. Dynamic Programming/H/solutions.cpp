#include <iostream>
#include <vector>

int main() {
    int mod = 100;
    std::string a, b;
    std::cin >> a >> b;
    int n = a.size();
    int m = b.size();

    std::vector<std::vector<int>> dp;
    std::vector<std::vector<int>> res;
    for (size_t i = 0; i < n + 1; ++i) {
        if (i < mod) dp.emplace_back(m + 1);
        if (i > 0 && i % mod == 0){
            res.emplace_back(dp[0]);
        }
        for (size_t j = 0; j < m + 1; ++j) {
            if (i == 0 || j == 0) {
                dp[i % mod][j] = 0;
            } else{
                if (a[i - 1] == b[j - 1]) {
                    dp[i%mod][j] = dp[(i - 1)%mod][j - 1] + 1;
                } else {
                    dp[i%mod][j] = std::max(dp[(i-1) % mod][j], dp[i%mod][j-1]);
                }
            }
        }
    }
    std::string result;
    std::vector<int> tm;
    int i = n;
    int j = m;
    bool flag = false;
    while (i > 0 && j > 0) {
        if (i % mod == 0) {
            if (!flag) {
                flag = true;
                tm = dp[0];
                dp[0] = res[res.size() - 1];
                for (int k = i - mod + 1; k < i; ++k) {
                    for (int l = 0; l < m + 1; ++l) {
                        if (l == 0) dp[k % mod][l] = 0;
                        else{
                            if (a[k - 1] == b[l - 1]) dp[k%mod][l] = dp[(k - 1)%mod][l - 1] + 1;
                            else dp[k%mod][l] = std::max(dp[(k-1) % mod][l], dp[k%mod][l-1]);
                        }
                    }
                }
            }
            if (a[i - 1] == b[j - 1]) {
                result += a[i - 1];
                i--;
                j--;
                res.pop_back();
            }else {
                if (dp[mod - 1][j] >= tm[j-1]) {
                    i--;
                    res.pop_back();
                }
                else j--;
            }
        } else{
            flag = false;
            if (a[i - 1] == b[j - 1]) {
                result += a[i - 1];
                i--;
                j--;
            }else {
                if (dp[(i-1) % mod][j] >= dp[i%mod][j-1]) i--;
                else j--;
            }
        }
    }
    std::reverse(result.begin(), result.end());
    std::cout << result;
    return 0;
}

