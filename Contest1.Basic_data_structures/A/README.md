# Stack

## url: https://codeforces.com/group/PVbQ8eK2T4/contest/344001/problem/A

### A. Стек

ограничение по времени на тест1 секунда

ограничение по памяти на тест256 мегабайт

ввод: стандартный ввод

вывод: стандартный вывод

Реализуйте свой стек. Решения, использующие std::stack, получат 1 балл. Решения, хранящие стек в массиве, получат 1.5 балла. Решения, использующие указатели, получат 2 балла.

Гарантируется, что количество элементов в стеке ни в какой момент времени не превышает 10000.

Обработайте следующие запросы:

push 𝑛: добавить число 𝑛 в конец стека и вывести «ok»;

pop: удалить из стека последний элемент и вывести его значение, либо вывести «error», если стек был пуст;

back: сообщить значение последнего элемента стека, либо вывести «error», если стек пуст;

size: вывести количество элементов в стеке;

clear: опустошить стек и вывести «ok»;

exit: вывести «bye» и завершить работу.

Входные данные

В каждой строке входных данных задана одна операция над стеком в формате, описанном выше.

Выходные данные

В ответ на каждую операцию выведите соответствующее сообщение.
