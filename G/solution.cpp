#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct Heap{

    std::vector<long long> values;                  //values of elements of heap

    void print(){
        std::cout << "heap is {: ";
        for (long long& i:values) {
            std::cout << i << " ";
        }
        std::cout << ":}\n";
    }         //print for debug

    void insert(long long num){
        values.push_back(num);                          //insert value in heap
        siftUp(values.size()-1);        //correct-check of heap
    }

    void siftUp(long long ind){
        if (ind != 0){      //check if elements has parents
            long long parent_ind = (ind - 1)/2;         //index of parent element
            if (values[ind] < values[parent_ind]){      //check if element is less than parent

                std::swap(values[ind], values[parent_ind]);         //swap value

                siftUp(parent_ind);         //correct-check of heap
            }
        }
    }

    void siftDown(long long ind){
        if (2*ind + 1 < values.size()){         //check if element has child
            long long min_child = 2*ind + 1;            //index of minimum child
            if (2*(ind + 1) < values.size()) {       //check if element has second child
                if (values[2 * (ind + 1)] < values[min_child]) {
                    min_child = 2 * (ind + 1);        //we change index to minimum child
                }
            }
            if (values[ind] > values[min_child]){       //check if child is less than element

                std::swap(values[ind], values[min_child]);      //swap elements

                siftDown(min_child);        //correct-check of heap
            }
        }

    }

    void extractMin(){
        std::swap(values[0], values[values.size()-1]);          //swap values of last element and minimum element

        values.pop_back();                  //delete minimum element
        siftDown(0);        //correct-check of heap
    }
    void extractMax(long long index){
        std::swap(values[index], values[values.size()-1]);          //swap values of last element and minimum element
        siftUp(index);
        values.pop_back();
    }

    long long getMax(){
        long long max_index = values.size()/2;
        for (long long i = values.size()/2; i < values.size(); ++i) {
            if (values[i] > values[max_index]){
                max_index = i;
            }
        }
        return max_index;
    }
};


int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);


    Heap heap;
    int amount = 0;
    std::string command;
    long long number;

    std::cin >> amount;

    for (int i = 0; i < amount; ++i) {
        std::cin >> command;
        if (command == "GetMin"){
            std::cout << heap.values[0] << "\n";
            heap.extractMin();
        }else if(command == "GetMax"){
            std::cout << heap.values[heap.getMax()] << "\n";
            heap.extractMax(heap.getMax());
        }else if(command[command.size()-1] == ')'){
            command = command.substr(7, command.size()-8);
            number = std::stoi(command);
            heap.insert(number);
        }
    }
    return 0;
}

