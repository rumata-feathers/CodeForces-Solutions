#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <deque>
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    long long collection, amount, quests, moves_amount = 0, car_number;
    std::cin >> collection >> amount >> quests;
    std::set<std::pair<long long, long long>> floor;
    std::map<long long, std::deque<long long>> cars;
    std::vector<long long> queue(quests+1);
    for (long long i = 1; i <= quests; ++i) {
        std::cin >> car_number;
        queue[i] = car_number;
        if (i < collection && cars.count(car_number) <= 0){
            cars.insert(std::pair<long long, std::deque<long long>>(car_number, std::deque<long long>(0)));
        }
        cars[car_number].push_back(i);
    }
    for (int i = 1; i <= quests; ++i) {
        car_number = queue[i];
        if (floor.find(std::pair<long long, long long>(cars[queue[i]].front(), queue[i])) != floor.end()) {
            if (!cars[car_number].empty()) floor.erase(std::pair<long long, long long>(cars[queue[i]].front(), queue[i]));
        }
        else {
            if (floor.size() == amount){
                floor.erase(std::prev(floor.end()));
            }
            moves_amount++;
        }
        cars[car_number].pop_front();
        if (!cars[car_number].empty()) floor.insert(std::pair<long long, long long>(cars[car_number].front(), car_number));
    }
    std::cout << moves_amount;
    return 0;
}

