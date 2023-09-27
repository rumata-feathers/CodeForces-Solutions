#include <iostream>
#include <stack>
#include <algorithm>

using ll = long long;
std::stack<ll> height_stack;
ll max_value = 0;

struct stack_of_min{
    std::stack<ll> da_stack;
    std::stack<ll> left_border;

    bool is_empty(){
        return da_stack.empty();
    }

    ll back(){
        return da_stack.top();
    }

};


void answer_change(ll new_el, ll index, stack_of_min* ptr){
    
        ll new_left_border = index+1;
        
        while(!(*ptr).is_empty() && new_el <= (ptr -> da_stack.top())){

            ll left_border = (ptr -> left_border.top());
            ll right_border = index + 1;
            ll square_width = (right_border - left_border);
            ll pop_number = (ptr -> da_stack.top());
             
            new_left_border = left_border;
            max_value = std::max(max_value, pop_number*square_width);
            new_left_border = left_border;
            ptr -> da_stack.pop();
            ptr -> left_border.pop();
            
        }

        if ( !(*ptr).is_empty() ) {
            ptr -> da_stack.push(new_el);
            ptr -> left_border.push(new_left_border);
            
        }else{
            ptr -> da_stack.push(new_el);
            ptr -> left_border.push(0);
            max_value = std::max(max_value, ptr -> da_stack.top()*(index + 1));
            
        }

}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    stack_of_min answer_stack;
    ll el_amount;
    ll counter = 0;
    std::cin >> el_amount;

    while (counter < el_amount){
        ll input_el;
        std::cin >> input_el;
        answer_change(input_el, counter - 1, &answer_stack);
        counter ++;
    }
    answer_change(0, counter - 1, &answer_stack);
    std::cout << max_value << std::endl;
    return 0;
}

