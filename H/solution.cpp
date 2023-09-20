#include <iostream>
#include <vector>


unsigned long long super_max_xxx_power(long long a,  long long b){
    unsigned long long c = 1;
    for (int i = 0; i < b; ++i) {
        c *= a;
    }
    return c;
}

void lsd_sort(std::vector<long long>& numbers, std::vector<long long>& copy_array, int bite_index){
    std::vector<long long> baskets(256);             //array of module

    unsigned long long basket_index;        //module

    for (long long& number : numbers) {
        basket_index = ((number) / super_max_xxx_power(256, bite_index)) % 256;      //get nodule of current bite
        baskets[basket_index] ++;       //increase basket with this module
    }
    for (int i = 1; i < baskets.size(); ++i) {
        baskets[i] += baskets[i-1];         //count amount before basket
    }


    long long position;             //position of number in sorted array

    for (long long i = numbers.size()-1; i >= 0; --i) {
        basket_index = ((numbers[i]) / super_max_xxx_power(256, bite_index)) % 256;
        position = baskets[basket_index] - 1;
        copy_array[position] = numbers[i];
        baskets[basket_index]--;                    //decrease so prev numbers go before
    }

}



int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    
    int amount;
    std::cin >> amount;

    std::vector<long long> numbers;
    long long number;


    for (int i = 0; i < amount; ++i) {
        std::cin>>number;
        numbers.push_back(number);
    }

    std::vector<long long> copy_array(numbers.size());


    for (int i = 0; i < 8; ++i) {
        if (i % 2 == 0){
            lsd_sort(numbers, copy_array, i);
        }else{
            lsd_sort(copy_array, numbers, i);
        }
    }
    for (long long& i: numbers) {
        std::cout << i << " ";
    }
    return 0;
}

