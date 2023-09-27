#include <iostream>
#include <vector>

int main() {
  int n, m;
  int mod = 1000000007;
  std::cin >> n >> m;
  std::vector<std::vector<char>> input(n, std::vector<char>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cin >> input[i][j];
    }
  }
  int ans = 1;
  for (int i = 0; i < n; ++i) {
    std::vector<bool> cor = {false, false};
    for (int j = 0; j < m; ++j) {
      if (input[i][j] == '+') cor[(j + 1) % 2] = true;
      if (input[i][j] == '-') cor[j % 2] = true;
    }
    if (cor[0] && cor[1]) ans = 0;
    if (!(cor[0] || cor[1])) ans = (ans*2) % mod;
  }
  int ans_tp = 1;
  for (int i = 0; i < m; ++i) {
    std::vector<bool> cor = {false, false};
    for (int j = 0; j < n; ++j) {
      if (input[j][i] == '+') cor[(j + 1) % 2] = true;
      if (input[j][i] == '-') cor[j % 2] = true;
    }
    if (cor[0] && cor[1]) ans_tp = 0;
    if (!(cor[0] || cor[1])) ans_tp = (ans_tp*2) % mod;
  }
  long long result = ans + ans_tp;
  bool flag_1 = true, flag_0 = true;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (input[i][j] == '+') {
        (i + j) % 2 == 0 ? flag_0 = false : flag_1 = false;
      }
      if (input[i][j] == '-') {
        (i + j) % 2 == 0 ? flag_1 = false : flag_0 = false;
      }
    }
  }
  result -= flag_1 + flag_0;
  std::cout << result % mod;
  return 0;
}

