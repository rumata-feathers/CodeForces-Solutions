#include <iostream>
#include <vector>

struct Heap{

    std::vector<long long> values;                  //values of elements of heap
    std::vector<long long> request_to_value;        //array of pointers from request to value
    std::vector<long long> value_to_request;        //array of pointers from values to request

    void print(bool long_print = true){
        std::cout << "heap is {: ";
        for (long long& i:values) {
            std::cout << i << " ";
        }
        std::cout << ":}\n";
        if (long_print) {
            std::cout << "index of each request is {: ";
            for (int i = 0; i < request_to_value.size(); ++i) {
                std::cout << i << " - " << request_to_value[i] << "  ";
            }
            std::cout << ":}\n";
            std::cout << "request of each value is {: ";
            for (long long &i: value_to_request) {
                std::cout << i << " ";
            }
            std::cout << ":}\n";
        }
    }         //print for debug

    void insert(long long num){
        values.push_back(num);                          //insert value in heap
        request_to_value.push_back(values.size()-1);    //now index of last request is last element of heap
        value_to_request.push_back(request_to_value.size()-1);   //request of last element now is current request
        siftUp(values.size()-1);        //correct-check of heap
    }

    void siftUp(long long ind){
        if (ind != 0){      //check if elements has parents
            long long parent_ind = (ind - 1)/2;         //index of parent element
            if (values[ind] < values[parent_ind]){      //check if element is less than parent

                long long request = value_to_request[ind];      //request of current element
                long long parent_request = value_to_request[parent_ind];        //request of parent element

                std::swap(values[ind], values[parent_ind]);         //swap value
                std::swap(request_to_value[request], request_to_value[parent_request]); //swap indexes of requests
                std::swap(value_to_request[ind], value_to_request[parent_ind]);     //swap requests

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
                long long current_request = value_to_request[ind];
                long long child_request = value_to_request[min_child];

                std::swap(values[ind], values[min_child]);      //swap elements
                std::swap(request_to_value[current_request], request_to_value[child_request]);  //swap indexes of requests
                std::swap(value_to_request[ind], value_to_request[min_child]);      //swap requests

                siftDown(min_child);        //correct-check of heap
            }
        }


    }

    void extractMin(){
        long long request_of_min_element = value_to_request[0];     //request of minimum element
        long long request_of_last_element = value_to_request[value_to_request.size()-1];        //request of last element


        request_to_value[request_of_min_element] = -1;          //as we extract element from heap, it's index is -1 now
        request_to_value[request_of_last_element] = 0;

        std::swap(values[0], values[values.size()-1]);          //swap values of last element and minimum element
        std::swap(value_to_request[0], value_to_request[value_to_request.size()-1]);        //swap requests of last element and first element

        values.pop_back();                  //delete minimum element
        value_to_request.pop_back();        //delete request of element

        request_to_value.push_back(-1);     //as we don't add element to heap, index of this request is -1

        siftDown(0);        //correct-check of heap
    }

    long long getMin(){
        request_to_value.push_back(-1);     //current request has no index in heap, so it's -1

        return values[0];
    }

    void decreaseKey(long long request, long long delta){
        long long index_of_request = request_to_value[request];
        values[index_of_request] -= delta;

        request_to_value.push_back(-1);         //as we don't add element to heap, index of this request is -1

        siftUp(index_of_request);             //correct-check of heap
    }
};





int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    Heap heap;
    std::string command;
    int amount_of_requests = 0;
    std::cin >> amount_of_requests;
    for (int i = 0; i < amount_of_requests; ++i) {
        std::cin >> command;
        if (command == "insert"){
            long long num = 0;
            std::cin >> num;
            heap.insert(num);

        }else if (command == "getMin"){
            std::cout << heap.getMin() << "\n";

        }else if (command == "extractMin"){
            heap.extractMin();

        }else if (command == "decreaseKey"){
            long long request = 0;
            long long delta = 0;
            std::cin >> request >> delta;
            heap.decreaseKey(request - 1, delta);
        }
    }
    return 0;
}

