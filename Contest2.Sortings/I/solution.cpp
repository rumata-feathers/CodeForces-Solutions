#include <iostream>
#include <vector>
#include <algorithm>

int get_super_median(std::vector<int>& elements, int start, int finish){
    if (finish - start <= 5){
        std::sort(elements.begin() + start, elements.begin() + finish);
        return elements[(start + finish-1)/2];
    }
    int ptr = start;
    std::vector<int> medians;
    std::vector<int> five;
    while(finish > ptr){
        if (finish >= ptr + 5){
            std::sort(elements.begin() + ptr, elements.begin() + ptr + 5);
            medians.push_back((elements)[ptr + 2]);
        }else{
            std::sort(elements.begin() + ptr, elements.begin() + finish);
            medians.push_back(elements[(finish + ptr-1)/2]);
        }
        ptr += 5;
    }
    int super_super_median = get_super_median(medians, 0, medians.size());
    return super_super_median;
}

std::pair<int, int> three_parts_partition(std::vector<int>& elements, int start, int end, int median){
    std::vector<int> num_array_less;
    std::vector<int> num_array_equal;
    std::vector<int> num_array_more;
    for (int i = start; i < end; ++i) {
        if (elements[i] < median){
            num_array_less.push_back(elements[i]);
        }else if (elements[i] == median){
            num_array_equal.push_back(elements[i]);
        }else{
            num_array_more.push_back(elements[i]);
        }
    }
    for (int i = 0; i < num_array_less.size(); ++i) {
        elements[i + start] = num_array_less[i];
    }
    for (int i = 0; i < num_array_equal.size(); ++i) {
        elements[i + start + num_array_less.size()] = num_array_equal[i];
    }
    for (int i = 0; i < num_array_more.size(); ++i) {
        elements[i + start + num_array_less.size() + num_array_equal.size()] = num_array_more[i];
    }
    return std::make_pair(start + num_array_less.size(), start + num_array_less.size() + num_array_equal.size());
}

void quick_sort(std::vector<int>& elements, int start, int end){
    if (end - start > 5){
        int median = get_super_median(elements, start, end);

        int left = three_parts_partition(elements, start, end, median).first;
        int right = three_parts_partition(elements, start, end, median).second;
        quick_sort(elements, start, left);
        quick_sort(elements, right, end);
    }else{
        std::sort(elements.begin() + start, elements.begin() + end);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::vector<int> numbers;
    int length = 0;
    int number = 0;
    std::cin >> length;
    for (int i = 0; i < length; ++i) {
        std::cin >>  number;
        numbers.push_back(number);
    }
    quick_sort(numbers, 0, numbers.size());

    for (int i = 0; i < numbers.size(); ++i) {
        std::cout << numbers[i] << " ";
    }
    
    return 0;
}

