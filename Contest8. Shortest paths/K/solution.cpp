#include <iostream>
#include <vector>
#include <map>
#include <queue>

#define board_size 4
#define square_board_size 16
#define max_bit_size 64
#define end_position_hash 1311768467463790320

//we store position in bit mask 4 bits for num
// 0-3 - what's on 0 place, then what's on 1st..

uint64_t get_after_move_pos(uint64_t pos, int empty, int to) {
  auto res = pos;
  res -= ((pos >> (board_size * (square_board_size - 1 - to))) & ((1 << board_size) - 1))
      << (board_size * (square_board_size - 1 - to));
  res += (pos >> (board_size * (square_board_size - 1 - to))) & ((1 << board_size) - 1)
      << (board_size * (square_board_size - 1 - empty));
  return res;
}

int calculate_heuristic(uint64_t& s_pos, uint64_t& e_pos) {
  int evr = 0;
  std::vector<int> epos(square_board_size);
  for (int i = 0; i < square_board_size; ++i) {
    int end_tmp = (e_pos << board_size * (square_board_size - i - 1)) >> (max_bit_size - board_size);
    epos[end_tmp] = square_board_size - 1 - i;
  }
  for (int i = 0; i < square_board_size; ++i) {
    int start_tmp = (s_pos << board_size * (square_board_size - i - 1)) >> (max_bit_size - board_size);
    if (start_tmp == 0) continue;
    evr += std::abs((epos[start_tmp]) / board_size - (square_board_size - i - 1) / board_size)
        + std::abs((epos[start_tmp]) % board_size - (square_board_size - i - 1) % board_size);
  }
  return evr;
}

int calculate_move_heuristic(uint64_t& s_pos, uint64_t& e_pos, int to, int from) {
  int evr = 0;
  int start_tmp_from = (s_pos << board_size * (from)) >> (max_bit_size - board_size);
  int end_from = 0;
  for (int i = 0; i < square_board_size; ++i) {
    int end_tmp = (e_pos << board_size * (i)) >> (max_bit_size - board_size);
    if (end_tmp == start_tmp_from) {
      end_from = i;
      break;
    }
  }

  evr -= std::abs(end_from / board_size - from / board_size)
      + std::abs(end_from % board_size - from % board_size);
  evr += std::abs(end_from / board_size - (to) / board_size)
      + std::abs(end_from % board_size - (to) % board_size);
  return evr;
}

struct res_pos {
  res_pos(int i, res_pos* p_pos) : empty(i), prev(p_pos) {}
  int empty = 0;
  res_pos* prev = nullptr;
};

struct position {
  uint64_t pos = 0;
  int empty = 0;
  int from_start_evr = 0;
  int from_end_evr = 0;
  int path_len = 0;
  uint64_t prev = 0;
  position() = default;
  explicit position(position* other_pos)
      : pos(other_pos->pos),
        empty(other_pos->empty),
        from_start_evr(other_pos->from_start_evr),
        from_end_evr(other_pos->from_end_evr),
        path_len(other_pos->path_len),
        prev(other_pos->prev) {}
  explicit position(uint64_t& new_pos, uint64_t& start_pos, uint64_t& end_pos) : pos(new_pos) {
    for (int i = square_board_size; i > 0; --i) {
      int tmp = (pos << board_size * (i - 1)) >> (max_bit_size - board_size);
      if (tmp == 0) {
        empty = i - 1;
        break;
      }
    }
    from_start_evr = calculate_heuristic(pos, start_pos);
    from_end_evr = calculate_heuristic(pos, end_pos);
  }
  void go(int to, uint64_t& start_pos, uint64_t& end_pos) {
    uint64_t to_pos = (pos >> (board_size * (square_board_size - 1 - to))) & ((1 << board_size) - 1);
    uint64_t on_to_pos = to_pos << (board_size * (square_board_size - 1 - to));
    uint64_t on_empty_pos = to_pos << (board_size * (square_board_size - 1 - empty));
    from_start_evr += calculate_move_heuristic(pos, start_pos, empty, to);
    from_end_evr += calculate_move_heuristic(pos, end_pos, empty, to);
    pos -= on_to_pos;
    pos += on_empty_pos;
    empty = to;
  }
  int f() const {
    return path_len + (from_end_evr - from_start_evr) / 2;
  }
};

bool operator<(const position& x, const position& y) {
  return x.f() == y.f() ? (x.from_end_evr == y.from_end_evr ? x.path_len > y.path_len : x.from_end_evr > y.from_end_evr)
                        : x.f() > y.f();
}

class Heap {
 public:
  std::priority_queue<position*> heap;
  uint64_t start_pos = 0;
  uint64_t end_pos = 0;
  std::map<uint64_t, res_pos*> used;
  uint64_t iterate() {
    position* cur_pos = heap.top();
    heap.pop();
    if (used.find(cur_pos->pos) == used.end()) {
      res_pos* res = nullptr;
      if (cur_pos->pos != start_pos) res = new res_pos(cur_pos->empty, used[cur_pos->prev]);
      else res = new res_pos(cur_pos->empty, nullptr);
      used[cur_pos->pos] = res;

      // try to go left
      if (cur_pos->empty % board_size != 0) {
        if (used.find(get_after_move_pos(cur_pos->pos, cur_pos->empty, cur_pos->empty - 1)) == used.end()) {
          auto* go_right = new position(cur_pos);
          go_right->go(cur_pos->empty - 1, start_pos, end_pos);
          go_right->prev = cur_pos->pos;
          ++go_right->path_len;
          heap.push(go_right);
        }
      }
      //try to go right
      if (cur_pos->empty % board_size != board_size - 1) {
        if (used.find(get_after_move_pos(cur_pos->pos, cur_pos->empty, cur_pos->empty + 1)) == used.end()) {
          auto* go_left = new position(cur_pos);
          go_left->go(cur_pos->empty + 1, start_pos, end_pos);
          go_left->prev = cur_pos->pos;
          ++go_left->path_len;
          heap.push(go_left);
        }
      }
      //try to go up
      if (cur_pos->empty / board_size != board_size - 1) {
        if (used.find(get_after_move_pos(cur_pos->pos, cur_pos->empty, cur_pos->empty + board_size)) == used.end()) {
          auto* go_up = new position(cur_pos);
          go_up->go(cur_pos->empty + board_size, start_pos, end_pos);
          go_up->prev = cur_pos->pos;
          ++go_up->path_len;
          heap.push(go_up);
        }
      }
      //try to go down
      if (cur_pos->empty / board_size != 0) {
        if (used.find(get_after_move_pos(cur_pos->pos, cur_pos->empty, cur_pos->empty - board_size)) == used.end()) {
          auto* go_down = new position(cur_pos);
          go_down->go(cur_pos->empty - board_size, start_pos, end_pos);
          go_down->prev = cur_pos->pos;
          ++go_down->path_len;
          heap.push(go_down);
        }
      }
      uint64_t res_it =cur_pos->pos;
      delete cur_pos;
      return res_it;
    }
    delete cur_pos;
    return 0;
  }
};
std::string get_path(res_pos* path) {
  std::string res;
  while (path->prev != nullptr) {
    int empty_pos = path->empty;
    int empty_prev_pos = path->prev->empty;
    if (empty_pos - empty_prev_pos == 1) res += 'L';
    else if (empty_pos - empty_prev_pos == -1) res += 'R';
    else if (empty_pos - empty_prev_pos == board_size) res += 'U';
    else if (empty_pos - empty_prev_pos == -board_size) res += 'D';
    path = path->prev;
  }
  return res;
}

std::string get_rev_path(res_pos* path) {
  std::string res;
  while (path->prev != nullptr) {
    int empty_pos = path->empty;
    int empty_prev_pos = path->prev->empty;
    if (empty_pos - empty_prev_pos == 1) res += 'R';
    else if (empty_pos - empty_prev_pos == -1) res += 'L';
    else if (empty_pos - empty_prev_pos == board_size) res += 'D';
    else if (empty_pos - empty_prev_pos == -board_size) res += 'U';
    path = path->prev;
  }
  return res;
}


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int empty_placement = 0;
  uint64_t s_pos = 0;
  uint64_t e_pos = 1311768467463790320;
  for (uint64_t i = square_board_size; i > 0; --i) {
    uint64_t num;
    std::cin >> num;
    if (num == 0) empty_placement = square_board_size - i;
    s_pos += num << ((i - 1) * board_size);
  }

  auto* start_position = new position(s_pos, e_pos, s_pos);
  auto* end_position = new position(e_pos, e_pos, s_pos);
  Heap graph_forward;
  Heap graph_reverse;
  graph_forward.start_pos = s_pos;
  graph_forward.end_pos = end_position_hash;
  graph_forward.heap.push(start_position);
  graph_reverse.start_pos = end_position_hash;
  graph_reverse.end_pos = s_pos;
  graph_reverse.heap.push(end_position);


//check if solvable
  int inv = 0;
  for (int i = 0; i < square_board_size; ++i) {
    uint64_t i_pos = (s_pos >> (board_size * (square_board_size - 1 - i))) % (1 << board_size);
    if (i_pos != 0)
      for (int j = 0; j < i; ++j) {
        uint64_t j_pos = (s_pos >> (board_size * (square_board_size - 1 - j))) % (1 << board_size);
        if (j_pos > i_pos && j_pos != 0)
          ++inv;
      }
  }
  inv += empty_placement / board_size + 1;
  if (inv % 2 == 1) {
    std::cout << -1;
    return 0;
  }

  int queue = 0;
  while (true) {
    if (queue % 2 == 0) {
      uint64_t deleted_pos = graph_forward.iterate();
      if (deleted_pos == 0) continue;
      if (graph_reverse.used.find(deleted_pos) != graph_reverse.used.end()) {
        auto res_f = get_path(graph_forward.used[deleted_pos]);
        auto res_r = get_rev_path(graph_reverse.used[deleted_pos]);
        std::cout << res_f.size() + res_r.size() << '\n';
        std::reverse(res_f.begin(), res_f.end());
        std::cout << res_f + res_r;
        return 0;
      }
      ++queue;
    } else {
      uint64_t deleted_pos = graph_reverse.iterate();
      if (deleted_pos == 0) continue;
      if (graph_forward.used.find(deleted_pos) != graph_forward.used.end()) {
        auto res_f = get_path(graph_forward.used[deleted_pos]);
        auto res_r = get_rev_path(graph_reverse.used[deleted_pos]);
        std::cout << res_f.size() + res_r.size() << '\n';
        std::reverse(res_f.begin(), res_f.end());
        std::cout << res_f + res_r;
        return 0;
      }
      ++queue;
    }
  }
}

