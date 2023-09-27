#include <iostream>
#include <vector>
using ll = long long;
int main() {
    int capacity = 0;
    int ingots = 0;
    std::cin >> capacity >> ingots;
    std::vector<int> weights(ingots);
    std::vector<std::vector<int>> dp;
    for (int i = 0; i < ingots; ++i) {
        std::cin >> weights[i];
    }
    for (int i = 0; i <= ingots; ++i) {
        dp.emplace_back(capacity + 1);
        for (int j = 0; j < capacity + 1; ++j) {
            if (i > 0){
                if (j >= weights[i-1]){
                    dp[i][j] = std::max(dp[i-1][j], dp[i-1][j-weights[i-1]] + weights[i-1]);
                }else{
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
    }
    std::cout << dp[dp.size()-1][capacity];
    return 0;
}

