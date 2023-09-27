#include <iostream>
#include <algorithm>
struct AVL_tree{
    long long value = 0;
    int height = 0;
    int balance = 0;
    AVL_tree* left_son = nullptr;
    AVL_tree* right_son = nullptr;
};
void debug(AVL_tree* root){
    std::cout << root->value << '\t';
    if (root->left_son != nullptr){
        debug(root->left_son);
    }else std::cout << "-left\t";
    if (root->right_son != nullptr){
        debug(root->right_son);
    }else std::cout << "-right\t";
    std::cout << '\n';

}
void fix_vertex(AVL_tree* vertex){
    long long left_height = 0;
    long long right_height = 0;
    if (vertex->left_son != nullptr) left_height = vertex->left_son->height;
    if (vertex->right_son != nullptr) right_height = vertex->right_son->height;
    vertex->height = std::max(left_height, right_height) + 1;
    vertex->balance = left_height - right_height;
}

bool search(AVL_tree* vertex, long long value){
    if (vertex == nullptr) return false;
    if (vertex->value != value){
        if (value < vertex->value){
            return search(vertex->left_son, value);
        }else{
            return search(vertex->right_son, value);
        }
    } else{
        return true;
    }
}

AVL_tree* miniRotationLeft(AVL_tree* vertex){
    AVL_tree* right_son_copy = vertex->right_son;
    vertex->right_son = right_son_copy->left_son;
    right_son_copy->left_son = vertex;
    fix_vertex(vertex);
    fix_vertex(right_son_copy);
    return right_son_copy;
}
AVL_tree* miniRotationRight(AVL_tree* vertex){
    AVL_tree* left_son_copy = vertex->left_son;
    vertex->left_son = left_son_copy->right_son;
    left_son_copy->right_son = vertex;
    fix_vertex(vertex);
    fix_vertex(left_son_copy);
    return left_son_copy;
}
AVL_tree* balance(AVL_tree* vertex) {
    fix_vertex(vertex);
    if (vertex->balance == -2){
        int right_son_balance = vertex->right_son->balance;      //if diff < 0 than we have right_son
        if (right_son_balance == 1) vertex->right_son = miniRotationRight(vertex->right_son);
        return miniRotationLeft(vertex);
    }else if (vertex->balance == 2){
        int left_son_balance = vertex->left_son->balance;
        if (left_son_balance == -1) vertex->left_son = miniRotationLeft(vertex->left_son);
        return miniRotationRight(vertex);
    }
    return vertex;
}
AVL_tree* insert(AVL_tree* vertex, long long value){
    if (vertex == nullptr) return new AVL_tree{value, 1};
    if (value > vertex->value){
        vertex->right_son = insert(vertex->right_son, value);
    }else if (value < vertex->value){
        vertex->left_son = insert(vertex->left_son, value);
    }
    return balance(vertex);
}
AVL_tree* find_right(AVL_tree* vertex){
    if(vertex->right_son != nullptr) return find_right(vertex->right_son);
    else return vertex;
}
AVL_tree* find_left(AVL_tree* vertex){
    if (vertex->left_son != nullptr) return find_left(vertex->left_son);
    else return vertex;
}
AVL_tree* delete_min(AVL_tree* vertex){
    if (vertex->left_son == nullptr) return vertex->right_son;
    else{
        vertex->left_son = delete_min(vertex->left_son);
    }
    return balance(vertex);
}
AVL_tree* delete_key(AVL_tree* vertex, long long value){
    if (vertex == nullptr) return vertex;
    else if (vertex->value < value) vertex->right_son =  delete_key(vertex->right_son, value);
    else if (vertex->value > value) vertex->left_son =  delete_key(vertex->left_son, value);
    else{
        AVL_tree* right = vertex->right_son;
        AVL_tree* left = vertex->left_son;
        delete[] vertex;
        if (right == nullptr) return left;
        else{
            AVL_tree* minimum = find_left(right);
            minimum->right_son = delete_min(right);
            minimum->left_son = left;
            return balance(minimum);
        }
    }
    return balance(vertex);
}
AVL_tree* next(AVL_tree* vertex, long long value){
    if (vertex == nullptr) return vertex;
    if (value >= vertex->value) return next(vertex->right_son, value);
    else{
        if (next(vertex->left_son, value) == nullptr) return vertex;
        else return next(vertex->left_son, value);
    }
}
AVL_tree* prev(AVL_tree* vertex, long long value){
    if (vertex == nullptr) return vertex;
    else if (vertex->value >= value) return prev(vertex->left_son, value);
    else{
        if (prev(vertex->right_son, value) == nullptr) return vertex;
        else return prev(vertex->right_son, value);
    }
}

int main() {
    AVL_tree* root = nullptr;
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string init_command;
    int num = 0;
    while (std::cin >> init_command){
        std::cin >> num;
        if (init_command == "insert" || init_command == "+"){
            root = insert(root, num);
        }
        if (init_command == "exists"){
            if (search(root, num)) std::cout << "true" << '\n';
            else std::cout << "false" << '\n';
        }
        if (init_command == "next"){
            if (next(root, num) == nullptr) std::cout << "none" << '\n';
            else std::cout << next(root, num)->value << '\n';
        }
        if (init_command == "prev"){
            if(prev(root, num) == nullptr) std::cout << "none" << '\n';
            else std::cout << prev(root, num)->value << '\n';
        }
        if (init_command == "delete"){
            root = delete_key(root, num);
        }

    }
    return 0;
}

