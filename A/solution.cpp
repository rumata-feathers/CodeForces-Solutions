#include <iostream>
#include <string>
#include <vector>


int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);

    std::vector<std::string> arr;
    std::string  number = {" "};
    auto pointer = arr.cbegin();
    int ctr = 0;
    while (std::getline(std::cin, number) && number != "") {
        
        if (arr.size() > 0) {
            ctr = 0;
            pointer = arr.cbegin();
            while(ctr < arr.size() && arr[ctr] + number > number + arr[ctr]){
                ++ctr;
                ++pointer;
            }
            arr.emplace(pointer, number);

        }else{
            arr.push_back(number);
        }
        
    }
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i];
    }
    return 0;
}

