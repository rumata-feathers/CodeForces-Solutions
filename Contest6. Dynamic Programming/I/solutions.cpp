#include <iostream>
#include <vector>

void result(std::vector<std::vector<long long>> A){
    long long result = 0;
    for (long long i = 0; i < A.size(); ++i) {
        result += A[0][i] % 999999937;
    }
    std::cout << result % 999999937 << '\n';
}

void print(std::vector<std::vector<long long>> A) {
    std::cout << "MATRIX:\n";
    for (auto & i : A) {
        for (auto & j: i) {
            std::cout << j << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "-------\n";
}

std::vector<std::vector<long long>> multiply(std::vector<std::vector<long long>> A, std::vector<std::vector<long long>> B, size_t size) {
    std::vector<std::vector<long long>> C(size, (std::vector<long long>(size)));
    for (long long a_row = 0; a_row < size; ++a_row) {
        for (long long b_col = 0; b_col < size; ++b_col) {
            for (long long i = 0; i < size; ++i) {
                C[a_row][b_col] += (A[a_row][i] * B[i][b_col]) % 999999937;
            }
            C[a_row][b_col] %= 999999937;
        }
    }
    return C;
}

std::vector<std::vector<long long>> power(std::vector<std::vector<long long>> A, size_t n) {
    if (n == 1) {
        return A;
    }
    if (n % 2 == 1) {
        return multiply(A, power(A, n-1), A.size());
    }
    else {
        std::vector<std::vector<long long>> D = power(A, n/2);
        return multiply(D, D, D.size());
    }
}


int main() {
    std::vector<std::vector<long long>> A = {{1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 1, 0, 0}, {1, 1, 1, 1, 1}, {1, 1, 1, 0, 0}};
    long long n;
    std::cin >> n;
    while (n != 0) {
        result(power(A, n));
        std::cin >> n;
    }
}

