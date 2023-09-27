#include <iostream>
#include <unordered_map>
#include <queue>

struct graph {
  int len;
  std::unordered_map<long long, int> dist_start;
  std::unordered_map<long long, int> dist_end;
  std::queue<long long> bfs_queue_start;
  std::queue<long long> bfs_queue_end;
  static long long get_power(long long v, int p) {
    while (p > 0) {
      v *= 10;
      --p;
    }
    return v;
  }
  static long long reverse_part(long long v, int i, int j) {
    for (int k = 0; k < (j - i + 1) / 2; ++k) {
      auto i_pos = (v / get_power(1, i + k)) % 10;
      auto j_pos = (v / get_power(1, j - k)) % 10;
      v -= get_power(i_pos, i + k);
      v -= get_power(j_pos, j - k);
      v += get_power(j_pos, i + k);
      v += get_power(i_pos, j - k);
    }
    return v;
  }

  auto get_bfs_perm() {
    int dist = 0;
    while (true) {
      //try first
      if (dist % 2 == 0) {
        while (!bfs_queue_start.empty()) {
          auto tmp = bfs_queue_start.front();
          if (dist_start.find(tmp) != dist_start.end() && dist_start[tmp] > dist / 2 + 1)  break;
          bfs_queue_start.pop();
          for (int v = 0; v < len; ++v) {
            for (int j = v + 1; j < len; ++j) {
              long long val = reverse_part(tmp, v, j);
              if (dist_end.find(val) != dist_end.end())
                return dist_end[val] + dist_start[tmp] + 1;
              else {
                if (dist_start.find(val) == dist_start.end()) {
                  dist_start[val] = dist_start[tmp] + 1;
                  bfs_queue_start.push(val);
                }
              }
            }
          }
        }
      } else {
        while (!bfs_queue_end.empty()) {
          auto tmp = bfs_queue_end.front();
          if (dist_end.find(tmp) != dist_end.end() && dist_end[tmp] > dist / 2 + 1)  break;
          bfs_queue_end.pop();
          for (int v = 0; v < len; ++v) {
            for (int j = v + 1; j < len; ++j) {
              long long val = reverse_part(tmp, v, j);
              if (dist_start.find(val) != dist_start.end())
                return dist_start[val] + dist_end[tmp] + 1;
              else {
                if (dist_end.find(val) == dist_end.end()) {
                  dist_end[val] = dist_end[tmp] + 1;
                  bfs_queue_end.push(val);
                }
              }
            }
          }
        }
      }
      ++dist;
    }
  }
  explicit graph(long long s_pos, long long end_pos, int len) : len(len) {
    bfs_queue_start.push(s_pos);
    bfs_queue_end.push(end_pos);
    dist_end[end_pos] = 0;
    dist_start[s_pos] = 0;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  clock_t start = clock();

  int n;
  std::cin >> n;

  long long f_in = 0;
  for (int i = 0; i < n; ++i) {
    int let;
    std::cin >> let;
    f_in *= 10;
    if (let != 10) f_in += let;
  }

  long long s_in = 0;
  for (int i = 0; i < n; ++i) {
    int let;
    std::cin >> let;
    s_in *= 10;
    if (let != 10) s_in += let;
  }
  if (f_in == s_in) {
    std::cout << 0;
    return 0;
  }
  graph perm(f_in, s_in, n);
  std::cout << perm.get_bfs_perm() << '\n';
  return 0;
}
