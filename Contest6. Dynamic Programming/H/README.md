# H. Network

## url: https://codeforces.com/group/PVbQ8eK2T4/contest/371629/problem/H

### H. Сеть (1 балл)

ограничение по времени на тест1 секунда

ограничение по памяти на тест64 мегабайта

вводстандартный ввод

выводстандартный вывод

В компьютерной сети вашей фирмы 𝑛 компьютеров. В последнее время свитч, к которому они подключены, сильно барахлит, и потому не любые два компьютера могут связаться друг с другом. Кроме того, если компьютер 𝑎 обменивается информацией с компьютером 𝑏, то никакие другие компьютеры не могут в это время обмениваться информацией ни с 𝑎, ни c 𝑏. Вам необходимо вычислить максимальное количество компьютеров, которые могут одновременно участвовать в процессе обмена информацией.


Входные данные

В первой строке файла задано число 𝑛 (1⩽𝑛⩽18). Далее идут 𝑛 строк по 𝑛 символов, причём 𝑗-й символ 𝑖-й строки равен 'Y', если 𝑖-й и 𝑗-й компьютеры могут обмениваться информацией, иначе он равен 'N'. Верно, что 𝑖-й символ 𝑖-й строки всегда равен 'N' и, кроме того, матрица символов симметрична.


Выходные данные

Выведите максимальное количество компьютеров, которые могут одновременно участвовать в процессе обмена информацией.
