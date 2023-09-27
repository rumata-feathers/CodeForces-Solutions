#include <iostream>
#include <string>
 
struct my_stack{
    int value = 0;
    my_stack* prev = nullptr;
    int index = 0;
    bool empty = true;
 
 
    void push(int x) {
        index ++;
        if (!empty) {
            auto* n = new my_stack();   //создание памяти под новый элемент
            n -> value = value;     //присваивание значения
            n -> prev = prev;
            prev = n;       //сдвигаем на элемент
            value = x;
        }else {
            value = x;      //если стек пустой, создавать новый элемент не нужно
            empty = false;
        }
    }
 
 
    int back_value() {
        return value;       // возвращаем последний элемент
    }
 
 
    void pop() {
        if(index > 1) {         //проверка на пустой стек
            index --;
            value = prev -> value;        // перезаписываем значения элемента на предыдущий
            my_stack *new_prev = prev -> prev;   //сохраняем во временную переменную указатель на предыдущий элемент
            prev = new_prev;
        }else {
            index = 0;
            empty = true;
        }
    }
 
    int size() {
        return index;       //возвращаем индекс
 
    }
 
    bool is_empty() {
        return empty;
    }
 
    void clear() {       //функция очистки моего стека
        while (prev != nullptr) {
            pop();
        }
        index = 0;
        empty = true;
    }
};
 
int main() {
    my_stack new_stack;
    new_stack.prev = nullptr;
    new_stack.value = NULL;
 
    std::string string;     //вводимая команда
    std::cin >> string;
 
    while (string != "exit") {
 
        if (string == "push") {  //если вводим команду push
            int x;
            std::cin >> x;
 
            new_stack.push(x);
            std::cout << "ok" << std::endl;
        }
 
        if (string == "back") {  //если вводим команду back
            int x = new_stack.back_value();
 
            if (!new_stack.is_empty()) {
                std::cout << x << std::endl;
            } else {
                std::cout << "error" << std::endl;
            }
        }
 
        if (string == "pop") {  //если вводим команду pop
            int x = new_stack.back_value();
 
            if (!new_stack.is_empty()) {
                std::cout << x << std::endl;
                new_stack.pop();
            }else {
                std::cout << "error" << std::endl;
            }
        }
 
        if (string == "size") {  //если вводим команду size
            int x = new_stack.size();
            std::cout << x << std::endl;
        }
 
        if (string == "clear") {  //если вводим команду clear
            new_stack.clear();
            std::cout << "ok" << std::endl;
        }
 
        std::cin >> string;
 
    }
    std::cout << "bye" << std::endl;
    return 0;
 
}
