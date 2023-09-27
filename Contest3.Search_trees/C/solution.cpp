#include <iostream>
#include <vector>
#include <algorithm>

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
    long long value = 0;
    long long left = 0;
    long long right = 0;
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
            if (vertex - tree.size()/2 < numbers.size()){
                tree[vertex]->empty = false;
                tree[vertex]->value = numbers[vertex - tree.size()/2];
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
                tree[vertex]->value = tree_max(tree[vertex]->left_child->value, tree[vertex]->right_child->value);
            }
        }
    }


    void update_tree(long long vertex){
        tree[vertex]->value = tree_max(tree[vertex]->left_child->value, tree[vertex]->right_child->value);
        if (vertex != 0) update_tree((vertex - 1)/2);
    }

    void change_value(long long index, long long value){
        long long vertex_index = index + (tree.size())/2;
        tree[vertex_index]->value = value;
        update_tree((vertex_index - 1)/2);
    }

    long long get_max(long long vertex, long long left_border, long long right_border){
        if (tree[vertex]->left == left_border){
            if (tree[vertex]->right == right_border){
                return tree[vertex]->value;
            }
        }

        long long middle = (tree[vertex]->left + tree[vertex]->right) / 2;

        if (middle < left_border){
            return get_max(2*vertex + 2, left_border, right_border);
        }else if (middle >= right_border){
            return get_max(2*vertex + 1, left_border, right_border);
        }else{
            long long left_child_result = get_max(2*vertex + 1, left_border, middle);
            long long right_child_result = get_max(2*vertex + 2, middle + 1, right_border);
            return tree_max(left_child_result, right_child_result);
        }
    }

    long long get_closest_root(long long vertex, long long value){
        if (tree[vertex] == tree[(vertex - 1)/2]->right_child){
            if ((vertex - 1)/2 == 0){
                return  - 1;
            }else{
                return get_closest_root((vertex - 1)/2, value);
            }
        } else{
            if (tree[vertex/2]->right_child->value >= value){
                return 2*(vertex/2) + 2;
            }else{
                if (vertex != 0)return get_closest_root((vertex - 1)/2, value);
                else return -1;
            }
        }
    }

    long long get_closest_max(long long vertex, long long value){
        if(tree[vertex]->left == tree[vertex]->right){
            return vertex;
        }else{
            if (tree[vertex]->left_child->value >= value){
                return get_closest_max(2*vertex + 1, value);
            }else{
                return get_closest_max(2*vertex + 2, value);
            }
        }
    }

    void clear(){
        for (auto & i : tree) {
            delete i;
        }

        tree.erase(tree.begin(), tree.end());
        tree.shrink_to_fit();
    }
};

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    long long n_size, request_amount;
    std::cin >> n_size >> request_amount;

    std::vector<long long> numbers;
    long long number;

    for (long long i = 0; i < n_size; ++i) {
        std::cin >> number;
        numbers.push_back(number);
    }

    Segment_tree tree(numbers.size());
    tree.build_tree(0, numbers);

    long long req_1, req_2, req_3;

    for (int i = 0; i < request_amount; ++i) {
        std::cin >> req_1 >> req_2 >> req_3;
        if(req_1 == 0){
            tree.change_value(req_2 - 1, req_3);
        }else{
            long long index = req_2 - 1 + tree.tree.size()/2;
            long long root = tree.get_closest_root(index, req_3);
            if (tree.tree[index]->value >= req_3){
                root = index;
            }
            if (root == -1){
                std::cout << "-1\n";
            }else{
                std::cout << tree.get_closest_max(root, req_3) - tree.tree.size()/2 + 1<< "\n";
            }
        }
    }
    
    tree.clear();
    return 0;
}

