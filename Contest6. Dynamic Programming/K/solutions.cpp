#include <iostream>
#include <vector>

bool check(int& mask1, int& mask2, int& size) {
    bool a, b, c, d;
    for (int i = 0; i < size - 1; ++i) {
        a = ((mask1 >> i)&1);
        b = ((mask1 >> (i + 1))&1);
        c = ((mask2 >> i)&1);
        d = ((mask2 >> (i + 1))&1);
        if (a == b && c == d && a == c) return false;
    }
    return true;
}
std::string decrease(std::string a){
    int x = 0;
    std::reverse(a.begin(), a.end());
    while (a[x] == '0') {
        a[x] = '9';
        ++x;
    }
    --a[x];
    int i = a.size() - 1;
    while(a[i] == '0') {
        a.pop_back();
        --i;
    }
    std::reverse(a.begin(), a.end());
    return a;
}
std::string divide(std::string& a) {
    std::string res;
    int carry = 0;
    for (int i = 0; i < a.size(); ++i) {
        res.push_back((a[i] - '0' + carry * 10) / 2 + '0');
        carry = (a[i] - '0' + carry * 10) % 2;
    }
    std::reverse(res.begin(), res.end());
    int i = res.size() - 1;
    while(res[i] == '0') {
        res.pop_back();
        --i;
    }
    std::reverse(res.begin(), res.end());
    return res;
}

std::vector<std::vector<int>> multiply(std::vector<std::vector<int>>& A, std::vector<std::vector<int>> B, int mod) {
    std::vector<std::vector<int>> C(A.size(), (std::vector<int>(A.size())));
    for (int a_row = 0; a_row < A.size(); ++a_row) {
        for (int b_col = 0; b_col < B.size(); ++b_col) {
            for (int i = 0; i < B.size(); ++i) {
                C[a_row][b_col] += (A[a_row][i] % mod) * (B[i][b_col] % mod);
                C[a_row][b_col] %= mod;
            }
            C[a_row][b_col] %= mod;
        }
    }
    return C;
}
std::vector<std::vector<int>> power(std::vector<std::vector<int>>& A, std::string n, int mod) {
    if (n == "1") {
        return A;
    }
    if ((n[n.size() - 1] - '0') % 2 == 1) {
        n = decrease(n);
        return multiply(A, power(A, n, mod), mod);
    } else {
        n = divide(n);
        std::vector<std::vector<int>> D = power(A, n, mod);
        return multiply(D, D, mod);
    }
}


int main() {
    int n, mod;
    std::string m;
    std::cin >> m >> n >> mod;
    std::vector<std::vector<int>> D(1<<n, std::vector<int> (1<<n));
    for (int i = 0; i < 1<<n; ++i) {
        for (int j = 0; j < 1<<n; ++j) {
            D[i][j] = check(i, j, n);
        }
    }
    if (m == "1") {
        std::cout << ((1 << n) % mod);
        return 0;
    }
    m = decrease(m);
    D = power(D, m, mod);
    int result = 0;
    for (int i = 0; i < D.size(); ++i) {
        for (int j = 0; j < D.size(); ++j) {
            result += D[i][j] % mod;
            result %= mod;
        }
    }
    std::cout << result % mod;
    return 0;
}

