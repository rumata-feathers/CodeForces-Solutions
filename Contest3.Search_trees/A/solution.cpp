#include <iostream>
#include <vector>
#include <algorithm>

long long tree_min(long long &a, long long &b){
    return std::min(a, b);
}
long long tree_max(long long& a, long long& b){
    return std::max(a, b);
}
long long get_closest_power(long long number){
    long long tmp = 1;
    while (tmp < number){
        tmp *= 2;
    }
    return tmp;
}

struct Node{
    bool empty = true;
    long long value[2] = {0, 0};
    long long left = 0;
    long long right = 0;
    Node* parent = nullptr;
    Node* left_child = nullptr;
    Node* right_child = nullptr;

};

struct Segment_tree{
    std::vector<Node*> tree = std::vector<Node*>(0);

    explicit Segment_tree(long long size){
        long long tree_size = 2*get_closest_power(size) - 1;
        for (int i = 0; i < tree_size; ++i) {
            Node* tmp = new Node();
            tree.push_back(tmp);
        }
    }

    void build_tree(long long vertex, std::vector<long long> &numbers){
        if (vertex >= tree.size()/2){       //check if leaf
            tree[vertex]->left = vertex - tree.size()/2;
            tree[vertex]->right = vertex - tree.size()/2;
            tree[vertex]->parent = tree[vertex/2 + vertex%2 - 1];
            if (vertex - tree.size()/2 < numbers.size()){
                tree[vertex]->empty = false;
                tree[vertex]->value[0] = numbers[vertex - tree.size()/2];
                tree[vertex]->value[1] = numbers[vertex - tree.size()/2];
            }else{
                tree[vertex]->empty = true;
            }
        }else{
            build_tree(2*vertex + 1, numbers);
            build_tree(2*vertex + 2, numbers);
            tree[vertex]->left_child = tree[2*vertex + 1];
            tree[vertex]->right_child = tree[2*vertex + 2];
            tree[vertex]->left = tree[vertex]->left_child->left;
            tree[vertex]->right = tree[vertex]->right_child->right;

            if (tree[2*vertex + 1]->empty) {
                tree[vertex]->empty = true;
            }else{
                tree[vertex]->empty = false;
                tree[vertex]->value[0] = tree_min(tree[vertex]->left_child->value[0], tree[vertex]->right_child->value[0]);
                tree[vertex]->value[1] = tree_max(tree[vertex]->left_child->value[1], tree[vertex]->right_child->value[1]);
                tree[vertex]->parent = tree[vertex/2];
            }
        }

    }


    void update_tree(long long vertex){
        tree[vertex]->value[0] = tree_min(tree[vertex]->left_child->value[0], tree[vertex]->right_child->value[0]);
        tree[vertex]->value[1] = tree_max(tree[vertex]->left_child->value[1], tree[vertex]->right_child->value[1]);
        if (vertex != 0) update_tree((vertex - 1)/2);
    }

    void change_value(long long index, long long value){
        long long vertex_index = index + (tree.size())/2;
        tree[vertex_index]->value[0] = value;
        tree[vertex_index]->value[1] = value;
        update_tree((vertex_index - 1)/2);
    }

    long long get_function(long long vertex, long long left_border, long long right_border, long long function(long long&, long long&)){
        if (tree[vertex]->left == left_border){
            if (tree[vertex]->right == right_border){
                return function(tree[vertex]->value[0], tree[vertex]->value[1]);
            }
        }

        long long middle = (tree[vertex]->left + tree[vertex]->right) / 2;

        if (middle < left_border){
            return get_function(2*vertex + 2, left_border, right_border, function);
        }else if (middle >= right_border){
            return get_function(2*vertex + 1, left_border, right_border, function);
        }else{
            long long left_child_result = get_function(2*vertex + 1, left_border, middle, function);
            long long right_child_result = get_function(2*vertex + 2, middle + 1, right_border, function);
            return function(left_child_result, right_child_result);
        }
    }

    void print() {
        std::cout << "heap is {:\n";

        for (long long i = 0; i < tree.size(); ++i) {
            std::cout << i << " - [" << tree[i]->value[0] << " , " << tree[i]->value[1] << "] ";
            std::cout << "(" << tree[i]->left << ", " << tree[i]->right << ", " << tree  [i]->empty << ")\n";
        }

        std::cout << ":}\n\n";
    }
    void print_vertex(long long i){
        std::cout << i << " - [" << tree[i]->value[0] << " , " << tree[i]->value[1] << "] ";
        std::cout << "(" << tree[i]->left << ", " << tree[i]->right << ", " << tree  [i]->empty << ")\n";
    }

    void clearify(){
        std::cout << "..clearing memory..\n";

        for (int i = 0; i < tree.size(); ++i) {
            std::cout << "-delete vertex " << i << "\n";
            if (!tree.empty()) delete tree[i];
        }

        tree.erase(tree.begin(), tree.end());
        tree.shrink_to_fit();

        std::cout << "..memory cleared..";
    }
};

int main() {
    long long k = 100005;
    long long num;
    std::vector<long long> numbers;
    for (long long i = 1; i <= k; ++i) {
        num = (i * i)%12345 + (i * i * i)%23456;
        numbers.push_back(num);
    }
    Segment_tree min_tree(numbers.size());
    min_tree.build_tree(0, numbers);

    long long requests = 0;
    std::cin >> requests;
    long long com_1, com_2;
    for (int i = 0; i < requests; ++i) {
        std::cin >> com_1 >> com_2;
        if(com_1 > 0){
            long long min = min_tree.get_function(0, com_1 - 1, com_2 - 1, tree_min);
            long long max = min_tree.get_function(0, com_1 - 1, com_2 - 1, tree_max);
            std::cout << max-min << "\n";
        }else{
            com_1 *= -1;
            min_tree.change_value(com_1-1, com_2);
        }
    }

    return 0;
}

