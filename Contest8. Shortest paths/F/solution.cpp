#include <iostream>
#include <vector>
#include<climits>

void swap(int* x, int* y);

class MinHeap {
  std::vector<int> heap;
  std::vector<int> index;
  std::vector<int> reverse_index;
 public:
  static auto get_power(int p) {
    int count = 0;
    while (p >> 1 > 1) {
      ++count;
      p >>= 1;
    }
    while (count > 0) {
      p <<= 1;
      --count;
    }
    return p;
  }
  static auto parent(int i) { return (i - 1) / 2; }
  static auto left(int i) { return (2 * i + 1); }
  static auto right(int i) { return (2 * i + 2); }
  auto getMin() { return reverse_index[0]; }
  auto siftUp(int i) {
    while (i != 0 && heap[parent(i)] > heap[i])
    {
      std::swap(heap[i], heap[parent(i)]);
      std::swap(index[reverse_index[i]], index[reverse_index[parent(i)]]);
      std::swap(reverse_index[i], reverse_index[parent(i)]);
      i = parent(i);
    }
  }
  void siftDown(int i) {
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < get_power(heap.size()) && heap[l] < heap[i])
      smallest = l;
    if (r < get_power(heap.size()) && heap[r] < heap[smallest])
      smallest = r;
    if (smallest != i)
    {
      std::swap(heap[i], heap[smallest]);
      std::swap(index[reverse_index[i]], index[reverse_index[smallest]]);
      std::swap(reverse_index[i], reverse_index[smallest]);
      siftDown(smallest);
    }
  }
  auto extractMin(){
    int min = getMin();
    if (heap.size() == 1)
    {
      heap.erase(heap.begin());
      return min;
    }
    heap[0] = heap[heap.size() - 1];
    index[reverse_index[heap.size() - 1]] = 0;
    index[reverse_index[0]] = -1;
    reverse_index[0] = reverse_index[heap.size() - 1];
    reverse_index[heap.size() - 1] = -1;
    heap.erase(heap.end() - 1);
    siftDown(0);
    return min;
  }
  auto decreaseKey(int i, int new_val) {
    if (index[i] == -1) return;
    heap[index[i]] = new_val;
    siftUp(index[i]);
  }
  auto getVal(int i) { return heap[index[i]];}
  MinHeap(int capacity, int start_vert) {
    heap = std::vector<int>(capacity, INT_MAX);
    index = std::vector<int>(capacity);
    reverse_index = std::vector<int>(capacity);
    for (int i = 0; i < capacity; ++i) {
      index[i] = i;
      reverse_index[i] = i;
    }
    heap[start_vert] = 0;
    siftUp(start_vert);
  }
};


struct graph {
  int inf = INT_MAX;
  std::vector<std::vector<std::pair<int, int>>> g;
  MinHeap new_dist;
  std::vector<int> dist;
  auto dijkstra(int v) {
    for (int i = 0; i < g.size(); ++i) {
      //find min
      int min_v = new_dist.extractMin();
      //found min
      if (dist[min_v] == inf)
        continue;

      //relaxing
      for (auto to_path : g[min_v]) {
        if (dist[min_v] + to_path.second < dist[to_path.first]) {
          new_dist.decreaseKey(to_path.first, dist[min_v] + to_path.second);
          dist[to_path.first] = dist[min_v] + to_path.second;
        }
      }
    }
  }

  graph(int n, int m) : new_dist(MinHeap(n, m)) {
    g = std::vector<std::vector<std::pair<int, int>>>(n);
    dist = std::vector<int>(n, inf);
    dist[m] = 0;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n, m, s, t;
  std::cin >> n >> m >> s >> t;
  graph dijkstra(n, --s);

  for (int i = 0; i < m; ++i) {
    int u, v, cost;
    std::cin >> u >> v >> cost;
    --u;
    --v;
    dijkstra.g[u].push_back({v, cost});
    if (u != v) dijkstra.g[v].push_back({u, cost});
  }

  dijkstra.dijkstra(s);
  --t;
  if (dijkstra.dist[t] == dijkstra.inf) std::cout << -1;
  else std::cout << dijkstra.dist[t];

  return 0;
}

