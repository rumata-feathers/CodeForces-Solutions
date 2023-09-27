#include <iostream>
#include <vector>
#include <cstdio>

int choise(std::vector<int>* A, std::vector<int>* B, int l){
    for (int i = 0; i < l; ++i) {
        if ((*B)[i] <= (*A)[i]) {
            if (i == 0){
                return i;
            }
            else{
                if ((*B)[i-1] <= (*A)[i]){
                    return i-1;
                }else{
                    return i;
                }
            }
        }
    }
    return l-1;
}



int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::vector<std::vector<int>> incrs;
    std::vector<std::vector<int>> decrs;
    int n, m, l;
    std::cin >> n >> m >> l;
    for (int i = 0; i < n; ++i) {
        std::vector<int> mdl;
        incrs.push_back(mdl);
        for (int j = 0; j < l; ++j) {
            int x = 0;
            std::cin >> x;
            incrs[i].push_back(x);
        }
    }
    for (int i = 0; i < m; ++i) {
        std::vector<int> mdl;
        decrs.push_back(mdl);
        for (int j = 0; j < l; ++j) {
            int x = 0;
            std::cin >> x;
            decrs[i].push_back(x);
        }
    }
    int q = 0;
    std::cin >> q;
    for (int i = 0; i < q; ++i) {
        int a, b;
        std::cin >> a >> b;
        std::cout << choise(&incrs[a-1], &decrs[b-1], l) + 1 << "\n";
    }
    return 0;
}

