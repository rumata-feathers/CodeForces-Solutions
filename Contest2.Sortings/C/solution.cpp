#include <iostream>
#include <vector>
#include <algorithm>

int five_median(std::vector<int>& five){
    std::sort(five.begin(), five.end());
    return five[(five.size()-1)/2];
}
int get_smedian(std::vector<int>& elements){
    if (elements.size() == 1){
        return elements[0];
    }
    int ptr = 0;
    int smedian = 0;
    std::vector<int> five(5);
    std::vector<int> medians;
    while(elements.size() >= ptr*5 + 5){
        for (int i = 0; i < 5; ++i) {
            five[i] = elements[5*ptr+i];
        }

        medians.push_back(five_median(five));
        ptr++;
    }
    five.clear();
    int i = 0;
    
    while (5 * ptr + i + 1 < elements.size()){
        five.push_back(elements[5*ptr + i]);
        i ++;
    }
    if (i > 0){
        medians.push_back(five_median(five));
    }

    smedian = get_smedian(medians);
    return smedian;

}
std::pair<std::vector<int>, std::vector<int>> partition(std::vector<int>& elements, int median){
    std::vector<int> left;
    std::vector<int> right;
    for (int i = 0; i < elements.size(); ++i) {
        if (elements[i] < median){
            left.push_back(elements[i]);
        }
        if (elements[i] > median){
            right.push_back(elements[i]);
        }
    }
    return std::make_pair(left, right);
}
int long_select(std::vector<int>& elements, int k){
    if (elements.size() == 1){
        return elements[0];
    }
    int median = get_smedian(elements);
    std::vector<int> left_part, right_part;
    left_part = partition(elements, median).first;
    right_part = partition(elements, median).second;
    if (k < left_part.size()){
        return long_select(left_part, k);
    } else if (elements.size() - k <= right_part.size()){
        return long_select(right_part, k - (elements.size() - right_part.size()));
    } else{
        return median;
    }
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int> elements;
    int q_el = 0;
    int k = 0;
    int elmnt = 0;
    int k_stat = 0;
    int sup_median = 0;
    std::cin >> q_el >> k;
    for (int i = 0; i < q_el; ++i) {
        std::cin >> elmnt;
        elements.push_back(elmnt);
    }
    k_stat = long_select(elements, k);

    std::cout << k_stat;

    return 0;
}

