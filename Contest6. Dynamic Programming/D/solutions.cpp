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

bool check(size_t x) {
    long long res = 0;
    while(x > 0) {
        res += bool(x & 1);
        x /= 2;
    }
    if (res % 3 == 0) {
        return true;
    }
    return false;
}

std::vector<std::vector<size_t>> multiply(std::vector<std::vector<size_t>> A, std::vector<std::vector<size_t>> B) {
    std::vector<std::vector<size_t>> C(A.size(), (std::vector<size_t>(A.size())));
    for (size_t a_row = 0; a_row < A.size(); ++a_row) {
        for (size_t b_col = 0; b_col < B.size(); ++b_col) {
            for (size_t i = 0; i < B.size(); ++i) {
                C[a_row][b_col] += ((A[a_row][i] % 1000000007) * (B[i][b_col] % 1000000007)) % 1000000007;
            }
            C[a_row][b_col] %= 1000000007;
        }
    }
    return C;
}

std::vector<std::vector<size_t>> power(std::vector<std::vector<size_t>> A, size_t n) {
    if (n == 1) {
        return A;
    }
    if (n % 2 == 1) {
        return multiply(A, power(A, n-1));
    }
    else {
        std::vector<std::vector<size_t>> D = power(A, n/2);
        return multiply(D, D);
    }
}

int main() {
    int n = 0;
    size_t k = 0;
    std::cin >> n >> k;
    std::vector<size_t> input(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> input[i];
    }
    if (n == 1) {
        std::cout << 1;
        return 0;
    }
    if (k == 1) {
        std::cout << n;
        return 0;
    }
    std::vector<std::vector<size_t>> A(n, std::vector<size_t>(n));
    for (size_t  i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            A[i][j] = check(input[i] xor input[j]);
        }
    }
    A = power(A, k - 1);
    size_t result = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result += A[i][j] % (1000000007);
        }
    }
    std::cout << (result % 1000000007);
    return 0;
}

