# B. Ungrowing sequence

## url: https://codeforces.com/group/PVbQ8eK2T4/contest/368711/problem/B

### B. Невозрастающая подпоследовательность (2 балла, с код-ревью)

ограничение по времени на тест2 секунды

ограничение по памяти на тест256 мегабайт

вводстандартный ввод

выводстандартный вывод

Вам требуется написать программу, которая по заданной последовательности находит максимальную невозрастающую её подпоследовательность (то есть такую последовательность чисел 𝑎𝑖1,𝑎𝑖2,…,𝑎𝑖𝑘 (𝑖1<𝑖2<…<𝑖𝑘), что 𝑎𝑖1≥𝑎𝑖2≥…≥𝑎𝑖𝑘 и не существует последовательности с теми же свойствами длиной 𝑘+1).


Входные данные

В первой строке задано число 𝑛 — количество элементов последовательности (1≤𝑛≤239017). В последующих строках идут сами числа последовательности 𝑎𝑖, отделенные друг от друга произвольным количеством пробелов и переводов строки (все числа не превосходят по модулю 231−2).


Выходные данные

Вам необходимо выдать в первой строке выходного файла число 𝑘 — длину максимальной невозрастающей подпоследовательности. В последующих строках должны быть выведены (по одному числу в каждой строке) все номера элементов исходной последовательности 𝑖𝑗, образующих искомую подпоследовательность. Номера выводятся в порядке возрастания. Если оптимальных решений несколько, разрешается выводить любое.

