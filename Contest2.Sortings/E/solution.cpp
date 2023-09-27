#include <iostream>
#include <vector>
#include <algorithm>

struct Heap{

    std::vector<long long> values;                  //values of elements of heap

    void insert(long long num){
        values.push_back(num);                          //insert value in heap
        siftUp(values.size()-1);        //correct-check of heap
    }

    void siftUp(int ind){
        if (ind != 0){      //check if elements has parents
            int parent_ind = (ind - 1)/2;         //index of parent element
            if (values[ind] > values[parent_ind]){      //check if element is less than parent

                std::swap(values[ind], values[parent_ind]);         //swap value

                siftUp(parent_ind);         //correct-check of heap
            }
        }
    }

    void siftDown(int ind){
        if (2*ind + 1 < values.size()){         //check if element has child
            int min_child = 2*ind + 1;            //index of minimum child
            if (2*(ind + 1) < values.size()) {       //check if element has second child
                if (values[2 * (ind + 1)] > values[min_child]) {
                    min_child = 2 * (ind + 1);        //we change index to minimum child
                }
            }
            if (values[ind] < values[min_child]){       //check if child is less than element

                std::swap(values[ind], values[min_child]);      //swap elements

                siftDown(min_child);        //correct-check of heap
            }
        }


    }

    void extractMax(){
        std::swap(values[0], values[values.size()-1]);          //swap values of last element and minimum element
        values.pop_back();                  //delete minimum element
        siftDown(0);        //correct-check of heap
    }
};

int main() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    long long amount, k, first, x, y;
    std::cin >> amount >> k >> first >> x >> y;
    std::vector<long long> output_array;

    Heap heap;
    unsigned long long num = first;

    for (int i = 0; i < amount; ++i) {
        num = (num*x + y) % (1 << 30);
        heap.insert(num);
        if (i >= k) {
            heap.extractMax();
        }
    }
    for(long long i = heap.values.size()-1; i >= 0; --i){
        output_array.push_back(heap.values[0]);
        heap.extractMax();
    }
    for (long long i = output_array.size()-1; i >= 0; --i) {
        std::cout << output_array[i] << " ";
    }
    return 0;
}

