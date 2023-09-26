#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <list>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    long long n;
    int m, k;
    std::cin >> n >> m >> k;
    std::map<int, std::set<long long>> forest;
    std::map<long long, std::set<int>> inverse_forest;
    std::string command;
    int set_num;
    size_t num;
    for (int i = 0; i < k; ++i) {
        std::cin >> command;
        if (command == "ADD") {
            std::cin >> num >> set_num;
            if (forest.count(set_num)) forest[set_num].emplace(num);
            else {
                forest.insert(std::pair<int, std::set<long long>>(set_num, std::set<long long>{num}));
            }
            if (inverse_forest.count(num)) inverse_forest[num].insert(set_num);
            else{
                inverse_forest.insert(std::pair<long long, std::set<int>>(num, std::set<int>{set_num}));
            }
        }
        if (command == "DELETE"){
            std::cin >> num >> set_num;
            inverse_forest[num].erase(set_num);
            forest[set_num].erase(num);
        }
        if (command == "CLEAR"){
            std::cin >> set_num;
            for (long long j : forest[set_num]) {
                inverse_forest[j].erase(set_num);
            }
            forest[set_num].clear();
        }
        if (command == "LISTSET"){
            std::cin >> set_num;
            bool empty = true;
            for (long long j : forest[set_num]) {
                std::cout << j << ' ';
                empty = false;
            }
            if (empty) std::cout << "-1";
            std::cout << '\n';
        }
        if (command == "LISTSETSOF"){
            std::cin >> num;
            bool empty = true;
            for (long long j : inverse_forest[num]) {
                std::cout << j << ' ';
                empty = false;
            }
            if (empty) std::cout << "-1";
            std::cout << '\n';
        }
    }
    return 0;
}

