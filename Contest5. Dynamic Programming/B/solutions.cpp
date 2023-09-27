#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    std::vector<int> dp(n);
    std::vector<int> previous(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    int lb, rb, mb;
    for (int i = 0; i < n; ++i) {
        dp[i] = -1;
        lb = 0;
        rb = n - 1;
        while (rb > lb) {
            mb = (lb + rb) / 2;
            if (dp[mb] == -1 || arr[dp[mb]] < arr[i]) rb = mb;
            else lb = mb + 1;
        }
        dp[lb] = i;
        if (lb != 0) previous[i] = dp[lb - 1];
        else previous[i] = -1;
    }
    int k = 0;
    std::vector<int> answer;
    while (dp[k] != -1 && k < n) {
        ++k;
    }
    std::cout << k << '\n';
    int i = dp[k - 1];
    while (i > -1) {
        answer.push_back(i + 1);
        i = previous[i];
    }
    std::reverse(answer.begin(), answer.end());
    for (int j : answer) {
        std::cout << j << '\n';
    }
    return 0;
}

