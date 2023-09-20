#include <iostream>
#include <vector>
#include <algorithm>
int f(int x){
    return x & (x + 1);
}

int g(int x){
    return x | (x + 1);
}

void update(std::vector<std::vector<std::vector<int>>>& table, std::vector<int>& point, int amount){
    for (int i = point[0]; i < table.size(); i = g(i)) {
        for (int j = point[1]; j < table[i].size(); j = g(j)) {
            for (int k = point[2]; k < table[i][j].size(); k = g(k)) {
                table[i][j][k] += amount;
            }
        }
    }
}

size_t get_pref_sum(std::vector<std::vector<std::vector<int>>>& table, int y, int z, int x){
    size_t answer = 0;
    for (int i = y; i >= 0; i = f(i) - 1) {
        for (int j = z; j >= 0; j = f(j) - 1) {
            for (int k = x; k >= 0 ; k = f(k) - 1) {
                answer += table[i][j][k];
            }
        }
    }
    return answer;
}

size_t get_sum(std::vector<std::vector<std::vector<int>>>& table, std::vector<int>& close_corner, std::vector<int>& distant_corner){
    size_t answer = 0;
    answer += get_pref_sum(table, distant_corner[0], distant_corner[1], distant_corner[2]);
    if (close_corner[0] != 0) answer -= get_pref_sum(table, close_corner[0] - 1, distant_corner[1], distant_corner[2]);
    if (close_corner[1] != 0) answer -= get_pref_sum(table, distant_corner[0], close_corner[1] - 1, distant_corner[2]);
    if (close_corner[2] != 0) answer -= get_pref_sum(table, distant_corner[0], distant_corner[1], close_corner[2] - 1);
    if (close_corner[0] != 0 && close_corner[1] != 0) answer += get_pref_sum(table, close_corner[0] - 1, close_corner[1] - 1, distant_corner[2]);
    if (close_corner[0] != 0 && close_corner[2] != 0) answer += get_pref_sum(table, close_corner[0] - 1, distant_corner[1], close_corner[2] - 1);
    if (close_corner[1] != 0 && close_corner[2] != 0) answer += get_pref_sum(table, distant_corner[0], close_corner[1] - 1, close_corner[2] - 1);
    if (close_corner[0] != 0 && close_corner[1] != 0 && close_corner[2] != 0) answer -= get_pref_sum(table, close_corner[0] - 1, close_corner[1] - 1, close_corner[2] - 1);

    return answer;

}

void create_table(std::vector<std::vector<std::vector<int>>>& table, int max_size){
    for (int i = 0; i < max_size; ++i) {
        std::vector<std::vector<int>> mid_table(max_size);
        for (int j = 0; j < max_size; ++j) {
            mid_table[j] = std::vector<int>(max_size);
        }
        table.push_back(mid_table);
    }
}
void print_table(std::vector<std::vector<std::vector<int>>>& table){
    for (int i = 0; i < table.size(); ++i) {
        std::cout << "\nlayer - " << i << " {\n";
        for (int j = 0; j < table[i].size(); ++j) {
            for (int k = 0; k < table[j].size(); ++k) {
                std::cout << table[i][j][k] << "  ";
            }
            std::cout << '\n';
        }
        std::cout << "}\n";
    }
}

int main() {
    std::vector<std::vector<std::vector<int>>> table;
    int max_size = 0;
    std::cin >> max_size;
    create_table(table, max_size);
    char c = ' ';
    while (c != '3'){
        std::cin >> c;
        if (c == '1'){
            int amount = 0;
            std::vector<int> point(3);
            for (int i = 0; i < 3; ++i) {
                std::cin >> amount;
                point[i] = amount;
            }
            std::cin >> amount;
            update(table, point, amount);
        }else if (c == '2'){
            int num = 0;
            std::vector<int> point_1(3);
            std::vector<int> point_2(3);
            for (int i = 0; i < 6; ++i) {
                std::cin >> num;
                if (i < 3) point_1[i] = num;
                else point_2[i-3] = num;
            }
            std::cout << get_sum(table, point_1, point_2) << '\n';
        }
    }
    return 0;
}

