#include <iostream>
#include <vector>
#include <queue>

struct graph {
  std::vector<std::vector<std::vector<std::pair<char, uint8_t>>>> g;
  std::vector<std::pair<char, uint8_t>> path;
  auto bfs(std::pair<char, uint8_t> from, std::pair<char, uint8_t> to) {
    std::queue<std::pair<char, uint8_t>> queue;
    std::vector<std::vector<std::pair<char, uint8_t>>> parent(g.size(), std::vector<std::pair<char, uint8_t>>(g.size()));
    std::vector<std::vector<bool>> used(g.size(), std::vector<bool>(g.size(), false));
    queue.push(from);
    parent[from.first - 'a'][from.second - '1'] = std::pair<char, uint8_t>{-1, -1};
    used[from.first - 'a'][from.second - '1'] = true;

    while (!queue.empty()) {
      auto cur_sq = queue.front();
      queue.pop();
      for (auto & av_sq : g[cur_sq.first - 'a'][cur_sq.second - '1']) {
        if (av_sq == to) {
          parent[av_sq.first - 'a'][av_sq.second - '1'] = cur_sq;
          std::pair<char, uint8_t> i;
          for (i = av_sq; parent[i.first - 'a'][i.second - '1'] != std::pair<char, uint8_t>{-1, -1} ; i = parent[i.first - 'a'][i.second - '1']) {
            path.push_back(i);
          }
          path.push_back(i);
          return;
        }else if (!used[av_sq.first - 'a'][av_sq.second - '1']) {
          used[av_sq.first - 'a'][av_sq.second - '1'] = true;
          queue.push(av_sq);
          parent[av_sq.first - 'a'][av_sq.second - '1'] = cur_sq;
        }
      }
    }
  }
  graph(int n) {
    g = std::vector<std::vector<std::vector<std::pair<char, uint8_t>>>>(n, std::vector<std::vector<std::pair<char, uint8_t>>>(n));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        for (int k = 0; k < n; ++k) {
          for (int l = 0; l < n; ++l) {
            if (std::abs(i - k) == 2 and std::abs(l - j) == 1) g[i][j].push_back({'a' + k, '1' + l});
            if (std::abs(i - k) == 1 and std::abs(l - j) == 2) g[i][j].push_back({'a' + k, '1' + l});
          }
        }
      }
    }
  }
};
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::pair<char, uint8_t> from_sq;
  std::cin >> from_sq.first >> from_sq.second;

  std::pair<char, uint8_t> to_sq;
  std::cin >> to_sq.first >> to_sq.second;

  if (from_sq == to_sq) {
    std::cout << from_sq.first << from_sq.second;
    return 0;
  }

  graph board(8);

  board.bfs(from_sq, to_sq);
  std::reverse(board.path.begin(), board.path.end());
  for (auto square: board.path) {
    std::cout << square.first << square.second << '\n';
  }
  return 0;
}

