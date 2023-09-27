#include <iostream>
#include <queue>
#include <deque>

std::deque<int> first_half;
std::queue<int> second_half;

void queue_push_at_end(int x){
    first_half.push_back(x);
}
void queue_pop(){
    std::cout << second_half.front() << std::endl;
    second_half.pop();
}
void push_mid(int x){
    first_half.push_front(x);
}
void check(){
    if(first_half.size() > second_half.size()){
        second_half.push(first_half.front());
        first_half.pop_front();
    }
}
int main() {
    int quests_amount = 0;
    std::string string;

    std::cin >> quests_amount;
    for (int i = 0; i < quests_amount; ++i) {
        std::cin >> string;
        if (string == "+"){
            int index = 0;
            std::cin >> index;
            queue_push_at_end(index);
        } else if (string == "*"){
            int index = 0;
            std::cin >> index;
            push_mid(index);
        }else if (string == "-"){
            queue_pop();
        }
        check();
    }
    return 0;
}

