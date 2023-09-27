#include <iostream>
#include <vector>
#include <algorithm>
int round(int a, int b){
    int ans = a/b;
    if (a%b > 0) ans++;
    return ans;
}
bool check(std::vector<int> enms, int p, int q, int k){
    int ctr = k;
    for (int i = 0; i < enms.size(); ++i) {
        if (ctr < 0) return false;
        if (enms[i] > k*q){
            if (p - q > 0) ctr -= round(enms[i] - k*q, p-q);
            else return false;
        }
    }
    if (ctr >= 0){
        return true;
    }else{
        return false;
    }
}
int binary_search(std::vector<int> enms, int p, int q, int max_enm){
    int right_border = round(max_enm, q);
    int left_border = 0;
    int middle = round(right_border+left_border, 2);
    while (right_border - middle > 0){
        if (check(enms, p, q, middle) == true){
            right_border = middle;
        }else{
            left_border = middle;
        }
        middle = round(right_border+left_border, 2);
    }
    return middle;

}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::vector<int> enemies;
    int n, p, q;
    int max_enm = 0;
    std::cin >> n >> p >> q;
    for (int i = 0; i < n; ++i) {
        int x = 0;
        std::cin >> x;
        max_enm = std::max(max_enm, x);
        enemies.push_back(x);
    }
    std::cout << binary_search(enemies, p, q, max_enm);
    return 0;
}

