#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

void print_vector(std::vector<std::pair<int, int>> &vec, const char *string = ""){
    std::cout << string << " {: ";
    for (auto& i : vec) {
        std::cout << "(" << i.first << ", " << i.second << ") ";
    }
    std::cout << ":}\n";
}
void print_vector(std::vector<int> &vec, const char *string = ""){
    std::cout << string << " {: ";
    for (int i : vec) {
        std::cout << i << " ";
    }
    std::cout << ":}\n";
}
void print_table(std::vector<std::vector<std::pair<int, int>>> &table, const char* name){
    std::cout << name << "\n";
    for (auto & i : table) {
        print_vector(i);
    }
}
void print_set(std::set<int> &nums, const char* name){
    std::cout << name << " {: ";
    for (int i : nums) {
        std::cout << i << " ";
    }
    std::cout << ":}\n";
}

std::pair<int, int> sec_kth(std::vector<int> &numbers, std::pair<int, int> f, std::pair<int, int> s){
    int a = f.first;
    int b = f.second;
    int c = s.first;
    int d = s.second;
    std::pair<int, int> answer;
    if(a != c){
        if (numbers[a] > numbers[c]){
            std::swap(a, c);
        }
        if (numbers[c] > numbers[b]){
            std::swap(b,c);
        }
        if (numbers[c] > numbers[d]){
            std::swap(c, d);
        }
        return std::make_pair(a, c);
    }else{
        if (numbers[b] > numbers[d]){
            std::swap(b,d);
        }
        return std::make_pair(a, b);
    }
}

void fill_log(std::vector<int> &logarithms){
    size_t counter = 1;
    logarithms[0] = 0;
    for (int i = 1; i < logarithms.size(); ++i) {
        logarithms[i] = logarithms[i-1];
        if (i + 1 >= (1<<counter)){
            logarithms[i]++;
            counter ++;
        }
    }
}

void create_table(std::vector<std::vector<std::pair<int, int>>> &table, int size, int max_power){
    for (int i = 0; i <= max_power; ++i) {
        table.emplace_back(size - (1 << i) + 1);
    }
}

void fill_table(std::vector<std::vector<std::pair<int, int>>> &table, std::vector<int> &numbers){
    //rows - степень
    //columns - элементы
    for (int i = 1; i < table.size(); ++i) {
        for (int j = 0; j < table[i].size(); ++j) {
            if (i == 1){
                if (numbers[j] <= numbers[j + 1]){
                    table[i][j].first = j;
                    table[i][j].second = j + 1;
                }else{
                    table[i][j].first = j + 1;
                    table[i][j].second = j;
                }
            }else{
                std::vector<int> nums;
                nums.push_back((table[i - 1][j].first));
                nums.push_back(table[i - 1][j].second);
                nums.push_back(table[i - 1][j + (1<<(i-1))].first);
                nums.push_back(table[i - 1][j + (1<<(i-1))].second);

                std::sort(nums.begin(), nums.end());
                table[i][j].first = sec_kth(numbers, table[i- 1][j], table[i - 1][j + (1<<(i-1))]).first;
                table[i][j].second = sec_kth(numbers, table[i- 1][j], table[i - 1][j + (1<<(i-1))]).second;
            }
        }
    }
}

int get_kth(std::vector<std::vector<std::pair<int, int>>>& table, std::vector<int>& numbers, std::vector<int> &deg, int left, int right){
    std::vector<int> nums;
    int length = right - left;
    int degree = deg[length];
    if ((left + (1 << degree)) == (right + 1)){
        return numbers[table[degree][left].second];
    }
    int index = sec_kth(numbers, table[degree][left], table[degree][right - (1 << degree) + 1]).second;
    return numbers[index];
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int array_size = 0;
    std::cin >> array_size;

    std::vector<int> numbers(array_size);
    std::vector<std::vector<std::pair<int, int>>> table;
    std::vector<int> logarithms(array_size);

    fill_log(logarithms);
    create_table(table, array_size, logarithms[logarithms.size()-1]);

    int requests_amount = 0, num = 0;
    std::cin >> requests_amount;
    for (int i = 0; i < array_size; ++i) {
        std::cin >> num;
        numbers[i] = num;
    }
    fill_table(table, numbers);
    int left, right;
    for (int i = 0; i < requests_amount; ++i) {
        std::cin >> left >> right;
        std::cout << get_kth(table, numbers, logarithms, left-1, right-1) << '\n';
    }
    return 0;
}

