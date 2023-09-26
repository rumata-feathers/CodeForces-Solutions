#include <iostream>

struct tree{
    long long key = 0;
    long long sum = 0;
    tree* left = nullptr;
    tree* right = nullptr;
    tree* parent = nullptr;
};

void print_tree(tree* root){
    if (root == nullptr) return;
    std::cout << '(' << root->key << ", " << root->sum << ')' << '\t';
    if (root->left != nullptr){
        print_tree(root->left);
    }else std::cout << "-left ";
    if (root->right != nullptr){
        print_tree(root->right);
    }else std::cout << "-right ";
    std::cout << ' ';
}

tree* create_leaf(long long key){
    tree* new_tree = new tree{key};
    return new_tree;
}

void set_parent(tree* current, tree* parent){
    if (current != nullptr) current->parent = parent;
}
void update_children(tree* current){
    set_parent(current->left, current);
    set_parent(current->right, current);
}
void recount(tree* vertex){
    if (vertex != nullptr) {
        vertex->sum = 0;
        if (vertex->left != nullptr) vertex->sum += vertex->left->sum + vertex->left->key;
        if (vertex->right != nullptr) vertex->sum += vertex->right->sum + vertex->right->key;
    }
}

void rotate_left(tree* vertex){
    if (vertex->parent->parent != nullptr) {
        if (vertex->parent->parent->left == vertex->parent) vertex->parent->parent->left = vertex;  //father is left son
        else vertex->parent->parent->right = vertex;    //father is right son
    }
    vertex->parent->right = vertex->left;
    set_parent(vertex->left, vertex->parent);
    vertex->left = vertex->parent;
    vertex->parent = vertex->left->parent;
    update_children(vertex);
    recount(vertex->left);
    recount(vertex);
    recount(vertex->parent);
}
void rotate_right(tree* vertex){
    if (vertex->parent->parent != nullptr) {
        if (vertex->parent->parent->left == vertex->parent) vertex->parent->parent->left = vertex;
        else vertex->parent->parent->right = vertex;
    }
    vertex->parent->left = vertex->right;
    set_parent(vertex->right, vertex->parent);
    vertex->right = vertex->parent;
    vertex->parent = vertex->parent->parent;
    update_children(vertex);
    recount(vertex->right);
    recount(vertex);
    recount(vertex->parent);
}

void zigi_zaga(tree* vertex){
    if (vertex == vertex->parent->left && vertex->parent == vertex->parent->parent->left){
        rotate_right(vertex->parent);
        rotate_right(vertex);
    }else if (vertex == vertex->parent->right && vertex->parent == vertex->parent->parent->left){
        rotate_left(vertex);
        rotate_right(vertex);
    }else if (vertex == vertex->parent->right && vertex->parent == vertex->parent->parent->right){
        rotate_left(vertex->parent);
        rotate_left(vertex);
    }else if (vertex == vertex->parent->left && vertex->parent == vertex->parent->parent->right){
        rotate_right(vertex);
        rotate_left(vertex);
    }
}

tree* splay(tree* vertex){
    while (vertex->parent != nullptr && vertex->parent->parent != nullptr){
        zigi_zaga(vertex);
    }
    if (vertex->parent != nullptr){
        if (vertex == vertex->parent->left) rotate_right(vertex);
        else rotate_left(vertex);
    }
    recount(vertex);
    return vertex;
}

tree* find_key(tree* vertex, long long key){
    if (vertex == nullptr) return vertex;
    if (vertex->key > key && vertex->left != nullptr) return find_key(vertex->left, key);
    else if (vertex->key < key && vertex->right != nullptr) return find_key(vertex->right, key);
    else return splay(vertex);
}
std::pair<tree*, tree*> split_by_key(tree* vertex, long long key){
    if (vertex == nullptr) return std::make_pair(nullptr, nullptr);
    vertex = find_key(vertex, key);
    if (vertex->key == key) {
        set_parent(vertex->left, nullptr);
        set_parent(vertex->right, nullptr);
        recount(vertex);
        return std::make_pair(vertex->left, vertex->right);
    }else if (vertex->key < key){
        tree* right_copy = vertex->right;
        vertex->right = nullptr;
        set_parent(right_copy, nullptr);
        recount(right_copy);
        recount(vertex);
        return std::make_pair(vertex, right_copy);
    }else{
        tree* left_copy = vertex->left;
        vertex->left = nullptr;
        set_parent(left_copy, nullptr);
        recount(left_copy);
        recount(vertex);
        return std::make_pair(left_copy, vertex);
    }
}
tree* insert(tree* root, long long key){
    std::pair<tree*, tree*> splitted_parts = split_by_key(root, key);
    tree* left_part = splitted_parts.first;
    tree* right_part = splitted_parts.second;
    root = create_leaf(key);
    root->left = left_part;
    root->right = right_part;
    update_children(root);
    recount(root);
    return root;
}
tree* merge_trees(tree* first_tree, tree* second_tree){
    if (first_tree == nullptr) return second_tree;
    if (second_tree == nullptr) return  first_tree;
    tree* new_second = find_key(second_tree, first_tree->key);
    new_second->left = first_tree;
    update_children(new_second);
    recount(new_second);
    return new_second;
}
std::pair<long long, tree*> count_sum(tree* root, long long left_border, long long right_border){
    bool denug = false;
    if (denug){ std::cout << "BEFORE SUM - ";print_tree(root);std::cout << '\n';}
    if (root == nullptr) return std::make_pair(0, nullptr);
    tree* new_root = find_key(root, left_border);
    tree* less_than_l_b;
    if (denug) {std::cout << "AFTER KEY FOUND - ";print_tree(new_root);std::cout << '\n';}
    if (new_root->key >= left_border){
        less_than_l_b = new_root->left;
        set_parent(less_than_l_b, nullptr);
        new_root->left = nullptr;
    }else{
        less_than_l_b = new_root;
        set_parent(new_root->right, nullptr);
        new_root = new_root->right;
        less_than_l_b->right = nullptr;
    }
    recount(new_root);
    recount(less_than_l_b);
    if (denug) {std::cout << "AFTER BALANCING - ";print_tree(new_root);std::cout << '\n';}

    new_root = find_key(new_root, right_border + 1);
    long long answer = 0;
    if (new_root != nullptr){
        if (new_root->key <= right_border) answer += new_root->key;
        if (new_root->left != nullptr) answer += new_root->left->sum + new_root->left->key;
    }
    if (denug) {std::cout << "AFTER SECOND SEARCH - ";print_tree(new_root);std::cout << '\n';}
    new_root = merge_trees(less_than_l_b, new_root);
    if (denug) {std::cout << "FINAL RESULT - ";print_tree(new_root);std::cout << '\n';}
    return std::make_pair(answer, new_root);
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    tree* root = nullptr;
    int quests_amount = 0;
    std::string quest_type, prev_quest_type;
    std::cin >> quests_amount;
    long long num_1, num_2, prev_answer;
    for (int i = 0; i < quests_amount; ++i) {
        prev_quest_type = quest_type;
        std::cin >> quest_type;
        if (quest_type == "+"){
            std::cin >> num_1;
            if (prev_quest_type == "?") root = insert(root, (num_1 + prev_answer)%1000000000);
            else root = insert(root, num_1);
        }
        if (quest_type == "?"){
            std::cin >> num_1 >> num_2;
            std::pair<long long, tree*> answer = count_sum(root, num_1, num_2);
            prev_answer = answer.first;
            root = answer.second;
            std::cout << prev_answer << '\n';
        }
    }
    return 0;
}

