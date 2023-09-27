#include <iostream>
#include <vector>

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
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int L, N, M;
  int mod = 1000000007;
  std::cin >> N >> L >> M;
  std::vector<std::vector<int>> scuttles(3, std::vector<int>(N));
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < N; ++j) {
      std::cin >> scuttles[i][j];
    }
  }
  std::vector<long long> start(M);
  for (int i = 0; i < N; ++i) {
    ++start[scuttles[0][i] % M];
  }
  std::vector<std::vector<long long>> A(M, std::vector<long long>(M));
  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < N; ++j) {
      ++A[i][(M - scuttles[1][j] + i) % M];
    }
  }
  if (L != 2) {
    A = power(A, L-2);
    std::vector<long long> res(M);
    for (int i = 0; i < M; ++i) {
      for (int j = 0; j < M; ++j) {
        res[i] += start[j] * A[i][j];
      }
    }
    start = res;
  }
  long long result = 0;
  for (int i = 0; i < N; ++i) {
    result += start[(2*M - scuttles[1][i] - scuttles[2][i]) % M];
    result %= mod;
  }
  std::cout << result % mod;
  return 0;
}

