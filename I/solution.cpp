#include <iostream>
#include <vector>
#include <algorithm>

void print(std::vector<std::pair<bool, int>>& segments){
    std::cout << "segments {: ";
    for (auto & segment : segments) {
        std::cout << "(" << segment.first << ", " << segment.second << ") ";
    }
    std::cout << ":}\n";
}

void push_color(std::vector<std::pair<bool, int>>& segments, size_t vertex){
    if (vertex < segments.size()/2 && segments[vertex].first){
        for (size_t i = 2*vertex + 1; i <= 2*vertex + 2; ++i) {
            segments[i].first = true;
            segments[i].second = segments[vertex].second;
        }
    }
    segments[vertex].first = false;
}

void update(std::vector<std::pair<bool, int>>& segments, size_t vertex){
    if (vertex > 0){
        size_t second_child = 4*((vertex - 1)/2 + 1) - 1 - vertex;
        if (segments[second_child].second != -1){
            segments[(vertex - 1)/2].second = std::min(segments[vertex].second, segments[second_child].second);
        }else{
            segments[(vertex - 1)/2].second = segments[vertex].second;
        }
        update(segments, (vertex - 1)/2);
    }
}
void build_tree(std::vector<std::pair<bool, int>>& segments, size_t vertex){
    if (2*vertex  + 1 < segments.size()){
        build_tree(segments, 2*vertex + 1);
        build_tree(segments, 2*vertex + 2);
        if (segments[2*vertex + 1].second == -1 && segments[2*vertex + 2].second == -1){
            segments[vertex].second = -1;
        }else if (segments[2*vertex + 1].second == -1){
            segments[vertex].second = segments[2*vertex + 2].second;
        }else if (segments[2*vertex + 2].second == -1){
            segments[vertex].second = segments[2*vertex + 1].second;
        }else{
            segments[vertex].second = std::min(segments[2*vertex + 1].second, segments[2*vertex + 2].second);
        }
    }
}

void paint(std::vector<std::pair<bool, int>>& segments, size_t vertex, int color, int left_border, int right_border, int tl, int tr){
    if (left_border > tr || right_border < tl){
        return;
    }
    push_color(segments, vertex);
    if (tl == left_border && tr == right_border){
        segments[vertex].first = true;
        segments[vertex].second = color;
        update(segments, vertex);
    }else if(tl <= tr){
        int middle = (tl + tr) / 2;
        if (middle < left_border){
            paint(segments, 2*vertex + 2, color, left_border, right_border, middle + 1, tr);
        }else if (middle > right_border){
            paint(segments, 2*vertex + 1, color, left_border, right_border, tl, middle);
        }else{
            paint(segments, 2*vertex + 1, color, left_border, middle, tl, middle);
            paint(segments, 2*vertex + 2, color, middle + 1, right_border, middle + 1, tr);
        }
    }

}

void fill(std::vector<std::pair<bool, int>>& segments){
    for (auto & segment : segments) {
        segment.second = -1;
    }
}

int get_closest_power(int& n){
    int power = 0;
    while ((1 << power) <= n){
        power++;
    }
    return power;
}

int get_brightness(std::vector<std::pair<bool, int>>& segments, size_t vertex, int left_border, int right_border, int tl, int tr){
    if (left_border > right_border){
        return -1;
    }
    if ((tl == left_border && tr == right_border) || (segments[vertex].first)){
        return segments[vertex].second;
    }
    int middle = (tl + tr) / 2;
    if (middle < left_border){
        return get_brightness(segments, 2*vertex + 2, left_border, right_border, middle + 1, tr);
    }else if (middle >= right_border){
        return get_brightness(segments, 2*vertex + 1, left_border, right_border, tl, middle);
    }else{
        int left_son_result = get_brightness(segments, 2*vertex + 1, left_border, middle, tl, middle);
        int right_son_result = get_brightness(segments, 2*vertex + 2, middle + 1, right_border, middle + 1, tr);
        if (left_son_result == -1 || right_son_result == -1){
            return left_son_result + right_son_result + 1;
        }else{
            return std::min(left_son_result, right_son_result);
        }
    }
}


int main() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    int n = 0;
    std::cin >> n;
    std::vector<std::pair<bool, int>> segments((1 << (get_closest_power(n) + 1))  - 1);
    fill(segments);
    int red, blue, green;
    for (int i = 0; i < n; ++i) {
        std::cin >> red >> blue >> green;
        segments[segments.size()/2 + i] = std::pair(false, red + blue + green);
    }
    build_tree(segments, 0);
//    print(segments);
    int requests = 0;
    std::cin >> requests;
    int left_border, right_border;
    int request_l, request_r;
    for (int i = 0; i < requests; ++i) {
        std::cin >> left_border >> right_border;
        std::cin >> red >> blue >> green;
        std::cin >> request_l >> request_r;
        paint(segments, 0, red + green + blue, left_border, right_border, 0, (1 << (get_closest_power(n)))  - 1);
//        print(segments);
        std::cout << get_brightness(segments, 0, request_l, request_r, 0, (1 << (get_closest_power(n)))  - 1) << ' ';
    }
    return 0;
}

