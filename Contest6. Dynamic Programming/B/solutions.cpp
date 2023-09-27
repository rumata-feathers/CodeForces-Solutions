#include <iostream>
#include "string"
#include <vector>
#include <algorithm>

long long quick_power(long long num, long long power, long long mod) {
  if (power == 0) {
    return 1;
  }
  if (power == 1) {
    return num%mod;
  }
  if (power % 2 == 1) {
    long long n = quick_power(num, power - 1, mod);
    n *= num % mod;
    return n % mod;
  }
  long long n = quick_power(num, power / 2, mod);
  n *= n;
  return n % mod;
}

int main() {
  std::cin.tie(nullptr);
  long long n;
  long long num, ans = -2, mod = 1000000007, inv_3 = 333333336, inv_2 = 500000004, inv__2 = 500000003;
  long long denom = 2;
  bool even = true, not_one = false;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::cin >> num;
    if (num % 2 == 0) even = false;
    if (num != 1) not_one = true;
    ans = quick_power(ans, num, mod);
    denom = quick_power(denom, num, mod);
  }
  if (!not_one) {
    std::cout << "0/1";
    return 0;
  }
  ans = (ans * inv__2) % mod;
  ans = (1 - ans) % mod;
  if (even) ans *= mod - 1;
  ans %= mod;
  ans = (ans * inv_3) % mod;
  if (ans < 0) ans += mod;
  std::cout << ans << '/';
  denom = (denom * inv_2) % mod;
  std::cout << denom;
  return 0;
}

