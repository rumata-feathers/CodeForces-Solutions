#include <iostream>

struct Node{
    long long value = 0;
    long long tl = 0;
    long long tr = 0;
    Node* left_child = nullptr;
    Node* right_child = nullptr;
    Node* parent = nullptr;
    Node(long long value, long long tl, long long tr, Node* left_child, Node* right_child, Node* parent): value(value), tl(tl), tr(tr), left_child(left_child), right_child(right_child), parent(parent){}
};

void update(Node& elmn, long long value){
    elmn.value += value;
    if (elmn.parent != nullptr){
        update(*elmn.parent, value);
    }
}

void add_leaf(Node& root, long long value)  {
    if (root.tl == root.tr){
        update(root, value);
    }else {
        long long middle = (root.tl + root.tr) / 2;
        if (value <= middle) {
            if (root.left_child == nullptr) {
                root.left_child = new Node(0, root.tl, middle, nullptr, nullptr, &root);
            }
            add_leaf(*root.left_child, value);
        } else {
            if (root.right_child == nullptr) {
                Node* ptr = new Node(0, middle + 1, root.tr, nullptr, nullptr, &root);
                root.right_child = ptr;
            }
            add_leaf(*root.right_child, value);
        }
    }
}

long long get_sum(Node& elmn, long long vertex){
    if (vertex == elmn.tr){

        return elmn.value;
    }
    long long mid = (elmn.tl + elmn.tr) / 2;
    if (mid <= vertex){
        long long answer = 0;
        if (elmn.left_child != nullptr){
            answer += elmn.left_child->value;
        }
        if (elmn.right_child != nullptr){
            answer += get_sum(*elmn.right_child, vertex);
        }
        return answer;
    }else{
        if (elmn.left_child != nullptr) {
            if ((*elmn.left_child).tl <= vertex) {
                return get_sum(*elmn.left_child, vertex);
            }
        }
        return 0;
    }

}

int main() {
    Node* root = new Node(0, 1, 1073741824, nullptr, nullptr, nullptr);

    int request = 0;
    std::cin >> request;

    char com;
    int num;

    for (int i = 0; i < request; ++i) {
        std::cin >> com >> num;
        if (com == '?'){
            if (num == 0){
                std::cout << 0 << '\n';
            }else{
                std::cout << get_sum(*root, num) << "\n";
            }
        }else{
            if (num != 0){
                add_leaf(*root, num);
            }
        }
    }
    return 0;
}

