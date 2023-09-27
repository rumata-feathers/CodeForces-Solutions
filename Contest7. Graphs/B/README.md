# B. Ancestor

## url: https://codeforces.com/group/PVbQ8eK2T4/contest/374347/problem/B

### B. Предок (1 балл, с код-ревью)

ограничение по времени на тест1 секунда

ограничение по памяти на тест256 мегабайт

вводстандартный ввод

выводстандартный вывод

Напишите программу, которая для двух вершин дерева определяет, является ли одна из них предком другой.


Входные данные

Первая строка входного файла содержит натуральное число 𝑛 (1≤𝑛≤100000) — количество вершин в дереве.


Во второй строке находится 𝑛 чисел. При этом 𝑖-е число второй строки определяет непосредственного родителя вершины с номером 𝑖. Если номер родителя равен нулю, то вершина является корнем дерева.


В третьей строке находится число 𝑚 (1≤𝑚≤100000)  — количество запросов. Каждая из следующих 𝑚 строк содержит два различных числа 𝑎 и 𝑏 (1≤𝑎,𝑏≤𝑛).


Выходные данные

Для каждого из 𝑚 запросов выведите на отдельной строке число 1, если вершина 𝑎 является одним из предков вершины 𝑏, и 0 в противном случае.
