#include <iostream>
#include <stack>

int main() {
    std::stack <int> psp;
    std::string str;
    std::cin >> str;
    for(int i=0; i < str.length(); i++){
        if (str[i] == '('){
            psp.push(0);
        }
        if (str[i] == '{'){
            psp.push(1);
        }
        if (str[i] == '['){
            psp.push(2);
        }
        if (str[i] == ')'){
            if(!psp.empty() && psp.top() == 0){
                psp.pop();
            }else{
                std::cout << "no" << std::endl;
                return 0;
            }
        }
        if (str[i] == '}'){
            if(!psp.empty() && psp.top() == 1){
                psp.pop();
            }else{
                std::cout << "no" << std::endl;
                return 0;
            }
        }
        if (str[i] == ']'){
            if(!psp.empty() && psp.top() == 2){
                psp.pop();
            }else{
                std::cout << "no" << std::endl;
                return 0;
            }
        }
    }
    if (psp.empty()){
        std::cout << "yes";
    }else{
        std::cout << "no" << std::endl;
    }
    return 0;
}
