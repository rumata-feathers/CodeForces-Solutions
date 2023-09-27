#include <iostream>
#include <vector>
#include <unordered_map>

#define board_size 4
#define square_board_size 16
#define max_bit_size 64

struct position {
  uint64_t pos;
  int evr;
  int empty;
  std::string path;
  position(position* other_pos)
      : pos(other_pos->pos),
        empty(other_pos->empty),
        evr(other_pos->evr),
        path(other_pos->path) {}
  explicit position(uint64_t new_pos) : pos(new_pos) {
    evr = 0;
    for (int i = square_board_size; i > 0; --i) {
      uint64_t tmp = pos;
      tmp <<= board_size * (i - 1);
      tmp >>= max_bit_size - board_size;
      int cur_pos = tmp;
      if (cur_pos == 0) {
        empty = i - 1;
        continue;
      }
      evr += std::abs((i - 1) / board_size - (cur_pos - 1) / board_size)
          + std::abs((i - 1) % board_size - (cur_pos - 1) % board_size);
    }
  }
  void heuristic(int to) {
    //manh dist
    int to_pos = (pos >> (board_size * (square_board_size - 1 - to))) % (1 << board_size);
    uint64_t on_to_pos = to_pos;
    on_to_pos <<= (board_size * (square_board_size - 1 - to));
    uint64_t on_empty_pos = to_pos;
    on_empty_pos <<= (board_size * (square_board_size - 1 - empty));
    evr -= std::abs((to_pos - 1) / board_size - to / board_size)
        + std::abs((to_pos - 1) % board_size - to % board_size);
    pos -= on_to_pos;
    pos += on_empty_pos;
    evr += std::abs((to_pos - 1) / board_size - empty / board_size)
        + std::abs((to_pos - 1) % board_size - empty % board_size);
    empty = to;
  }
  int f() {
    return evr;
  }
  bool check_end() const {
    return evr == 0;
  }
};

class MinHeap {
  std::vector<position*> heap;
 public:
  static int parent(size_t i) { return (i - 1) / 2; }
  static int left(size_t i) { return (2 * i + 1); }
  static int right(size_t i) { return (2 * i + 2); }
  position* getMin() { return heap[0]; }
  void siftUp(size_t i) {
    while (i != 0 && heap[parent(i)]->f() > heap[i]->f()) {
      std::swap(infrm[heap[i]->pos], infrm[heap[parent(i)]->pos]);
      std::swap(heap[i], heap[parent(i)]);
      i = parent(i);
    }
  }
  void siftDown(size_t i) {
    size_t l = left(i);
    size_t r = right(i);
    size_t smallest = i;
    if (l < heap.size() && heap[l]->f() < heap[i]->f())
      smallest = l;
    if (r < heap.size() && heap[r]->f() < heap[smallest]->f())
      smallest = r;
    if (smallest != i) {
      std::swap(infrm[heap[i]->pos], infrm[heap[smallest]->pos]);
      std::swap(heap[i], heap[smallest]);
      siftDown(smallest);
    }
  }
  position* extractMin() {
    position* min = getMin();
    if (heap.size() == 1) {
      heap.erase(heap.begin());
      return min;
    }
    heap[0] = heap[heap.size() - 1];
    infrm[heap[0]->pos] = 1;
    heap.erase(heap.end() - 1);
    siftDown(0);
    return min;
  }
  void insert(position* new_pos) {
    uint64_t new_pos_string = new_pos->pos;
    if (infrm.find(new_pos_string) == infrm.end()) {
      infrm[new_pos_string] = heap.size() + 1;
      heap.push_back(new_pos);
      siftUp(heap.size() - 1);
    } else {
      if (infrm[new_pos_string] == 0)
        return;
      if (heap[infrm[new_pos_string] - 1]->f() > new_pos->f()) {
        delete heap[infrm[new_pos_string] - 1];
        heap[infrm[new_pos_string] - 1] = new_pos;
        siftUp(infrm[new_pos_string] - 1);
      }else{
        delete new_pos;
      }
    }
  }
  bool empty() { return heap.empty(); }
  std::unordered_map<uint64_t, size_t> infrm;
  size_t size() { return heap.size(); }
  size_t map_size() { return infrm.size(); }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int empty_placement = 0;
  uint64_t s_pos = 0;
  for (uint64_t i = square_board_size; i > 0; --i) {
    uint64_t num;
    std::cin >> num;
    if (num == 0) empty_placement = square_board_size - i;
    s_pos += num << ((i - 1) * board_size);
  }

  position* start_position = new position(s_pos);
  MinHeap graph;
  graph.insert(start_position);

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

  while (!graph.empty()) {
    position* cur_pos = graph.extractMin();
    if (cur_pos->check_end()) {
      std::cout << cur_pos->path.size() << '\n' << cur_pos->path << '\n';
      return 0;
    } else {
      if (graph.infrm[cur_pos->pos] != 0) {
        // try to go left
        if (cur_pos->empty % board_size != 0) {
          position* go_right = new position(cur_pos);
          go_right->heuristic(cur_pos->empty - 1);
          go_right->path += 'R';
          graph.insert(go_right);
        }
        //try to go right
        if (cur_pos->empty % board_size != board_size - 1) {
          position* go_left = new position(cur_pos);
          go_left->heuristic(cur_pos->empty + 1);
          go_left->path += 'L';
          graph.insert(go_left);
        }
        //try to go up
        if (cur_pos->empty / board_size != board_size - 1) {
          position* go_up = new position(cur_pos);
          go_up->heuristic(cur_pos->empty + board_size);
          go_up->path += 'U';
          graph.insert(go_up);
        }
        //try to go down
        if (cur_pos->empty / board_size != 0) {
          position* go_down = new position(cur_pos);
          go_down->heuristic(cur_pos->empty - board_size);
          go_down->path += 'D';
          graph.insert(go_down);
        }
      }
    }
    graph.infrm[cur_pos->pos] = 0;
    delete cur_pos;
  }
  return 0;
}

