#include <iostream>
#include <vector>

void print(std::vector<std::vector<long long>>& A) {
    std::cout << "MATRIX:\n";
    for (auto & i : A) {
        for (auto & j: i) {
            std::cout << j << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "-------\n";
}

std::vector<std::vector<long long>> multiply(std::vector<std::vector<long long>> A, std::vector<std::vector<long long>> B) {
    std::vector<std::vector<long long>> C(A.size(), (std::vector<long long>(A.size())));
    for (long long a_row = 0; a_row < A.size(); ++a_row) {
        for (long long b_col = 0; b_col < B.size(); ++b_col) {
            for (long long i = 0; i < B.size(); ++i) {
                C[a_row][b_col] += ((A[a_row][i] % 1000000007) * (B[i][b_col] % 1000000007)) % 1000000007;
            }
            C[a_row][b_col] %= 1000000007;
        }
    }
    return C;
}

std::vector<std::vector<long long>> power(std::vector<std::vector<long long>> A, long long n) {
    if (n == 1) {
        return A;
    }
    if (n % 2 == 1) {
        return multiply(A, power(A, n-1));
    }
    else {
        std::vector<std::vector<long long>> D = power(A, n/2);
        return multiply(D, D);
    }
}

int main() {
    std::cin.tie(nullptr);
    long long n;
    long long k;
    std::cin >> n >> k;
    std::vector<std::vector<long long>> input(n, std::vector<long long>(3));
    for (long long i = 0; i < n; ++i) {
        std::cin >> input[i][0] >> input[i][1] >> input[i][2];
    }
    long long max_height = 17;
    std::vector<std::vector<long long>> A(max_height, std::vector<long long>(max_height));
    A[0][0] = 1;
    std::vector<std::vector<long long>> B(max_height, std::vector<long long>(max_height));
    for (long long i = 0; i < n; ++i) {
        //fill matrix
        for (long long row = 0; row < max_height; ++row) {
            for (long long col = 0; col < max_height; ++col) {
                if (row > input[i][2]) B[row][col] = 0;
                else{
                    B[row][col] = 0;
                    if (row != 0) B[row][row - 1] = 1;
                    B[row][row] = 1;
                    if (row != input[i][2]) B[row][row + 1] = 1;
                }
            }
        }
        //get in power
        B = power(B, std::min(k, input[i][1]) - input[i][0]);
        A = multiply(A, B);
    }
    std::cout << A[0][0] % 1000000007;
    return 0;
}

