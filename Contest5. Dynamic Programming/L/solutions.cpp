#include <iostream>
#include <vector>
int main() {
    long long n = 0;
    std::cin >> n;
    std::vector<long long> weights(n);
    for (long long i = 0; i < n; ++i) {
        std::cin >> weights[i];
    }
    long long capacity = 0;
    std::cin >> capacity;
    std::vector<long long> f_sum, s_sum;
    long long current_sum;
    for (long long i = 0; i < (1 << n/2); ++i) {
        current_sum = 0;
        for (long long j = 0; j < n/2; ++j) {
            if ((i >> j) & 1) {
                current_sum += weights[j];
            }
        }
        f_sum.push_back(current_sum);
    }
    for (long long i = 0; i < (1 << (n - n/2)); ++i) {
        current_sum = 0;
        for (long long j = 0; j < n - n/2; ++j) {
            if ((i >> j) & 1) {
                current_sum += weights[n/2 + j];
            }
        }
        s_sum.push_back(current_sum);
    }
    std::sort(f_sum.begin(), f_sum.end());
    std::sort(s_sum.begin(), s_sum.end());
    long long u_b, b_b, m_b;
    long long result = 0;
    for (long long i : f_sum) {
        b_b = 0;
        u_b = s_sum.size()-1;
        while (b_b < u_b) {
            m_b = (u_b + b_b) >> 1;
            if (s_sum[m_b] > capacity - i) u_b = m_b;
            else b_b = m_b + 1;
        }
        result += b_b;
        if (s_sum[b_b] <= capacity - i && i <= capacity) ++result;
    }
    std::cout << result;
    return 0;
}

