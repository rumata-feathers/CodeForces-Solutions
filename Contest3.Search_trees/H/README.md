# H. Second Statistic (RMQ)

## url: https://codeforces.com/group/PVbQ8eK2T4/contest/350943/problem/H

### H. Вторая статистика (RMQ)

ограничение по времени на тест1 секунда

ограничение по памяти на тест64 мегабайта

вводстандартный ввод

выводстандартный вывод


Дано число 𝑁 и последовательность из 𝑁 целых чисел. Найти вторую порядковую статистику на заданных диапазонах.


Для решения задачи используйте структуру данных Sparse Table. Требуемое время обработки каждого диапазона 𝑂(1). Время подготовки структуры данных 𝑂(𝑛log𝑛).


Входные данные

В первой строке заданы 2 числа: размер последовательности 𝑁 и количество диапазонов 𝑀.


Следующие 𝑁 целых чисел задают последовательность. Далее вводятся 𝑀 пар чисел - границ диапазонов.



Выходные данные

Для каждого из M диапазонов напечатать элемент последовательности - 2ю порядковую статистику. По одному числу в строке.


