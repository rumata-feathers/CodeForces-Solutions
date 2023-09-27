#include <iostream>
#include <vector>

long long inverse_counter = 0;

std::vector<int> merge(std::vector<int> left_half, std::vector<int> right_half){
    std::vector<int> merged_array;
    int deleted = 0;

    while (!left_half.empty() || !right_half.empty()){
        if (left_half.empty()){
            merged_array.push_back(right_half[0]);
            right_half.erase(right_half.begin());
        }
        else if (right_half.empty()){
            merged_array.push_back(left_half[0]);
            left_half.erase(left_half.begin());
            inverse_counter += deleted;
        }
        else if(left_half[0] <= right_half[0]){
            merged_array.push_back(left_half[0]);
            left_half.erase(left_half.begin());
            inverse_counter += deleted;
        } else{
            merged_array.push_back(right_half[0]);
            right_half.erase(right_half.begin());
            deleted ++;
        }
    }
    return merged_array;
}
std::vector<int> merge_sort(std::vector<int> numbers){
    if (numbers.size() == 1) return numbers;
    std::vector<int> left_half;
    for (int i = 0; i < numbers.size()/2; ++i) {
        left_half.push_back(numbers[0]);
        if (!numbers.empty()) numbers.erase(numbers.begin());
    }
    left_half = merge_sort(left_half);
    numbers = merge_sort(numbers);
    numbers = merge(left_half, numbers);
    return numbers;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    freopen("inverse.in", "r", stdin);
    freopen("inverse.out", "w", stdout);
    std::vector<int> num;
    int quests_amount;
    std::cin >> quests_amount;
    for (int i = 0; i < quests_amount; ++i) {
        int x = 0;
        std::cin >> x;
        num.push_back(x);
    }
    std::vector<int> e = merge_sort(num);
    std::cout << inverse_counter;
    return 0;
}
