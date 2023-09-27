#include <iostream>
#include <vector>
#include <algorithm>


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 0;
    int left_border = 0;
    int right_border = 0;
    int cuts_sum = 0;
    std::vector<std::pair<int, int>> offcut;
    std::pair<int, int> last_cut;
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        std::cin >> left_border >> right_border;
        if (left_border <= right_border){
            offcut.push_back(std::pair<int, int>(left_border, right_border));
        } else{
            offcut.push_back(std::pair<int, int>(right_border, left_border));
        }
    }

    std::sort(offcut.begin(), offcut.end(), [](auto &left, auto &right) {
        if (left.first == right.first){
            if (left.second < right.second){
                return true;
            }else{
                return false;
            }
        } else if (left.first < right.first) {
            return true;
        }else{
            return false;
        }
    });
    for (int i = 0; i < offcut.size(); ++i) {
        if (i == 0){
            last_cut = offcut[i];
        }else{
            if (offcut[i].second <= last_cut.second){
                cuts_sum += std::max(0, offcut[i].first - last_cut.first);
                last_cut.first = std::max(offcut[i].second, last_cut.first);
            }else{
                cuts_sum += std::max(0, std::min(last_cut.second, offcut[i].first) - last_cut.first);
                last_cut.first = std::max(offcut[i].first, last_cut.second);
                last_cut.second = offcut[i].second;
            }
        }
    }
    cuts_sum += last_cut.second - last_cut.first;
    std::cout << cuts_sum;
    return 0;
}

