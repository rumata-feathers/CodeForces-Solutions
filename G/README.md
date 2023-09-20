# G. Minimum and Maximum

## url: https://codeforces.com/group/PVbQ8eK2T4/contest/347382/problem/G


### G. Minimum and maximum

time limit per test1 second

memory limit per test256 megabytes

inputstandard input

outputstandard output


Consider a multiset of integer numbers (a set with possible repetitions). You are to implement a data structure for the storage of this multiset, supporting the following operations:

- GetMin — extraction of the minimum value;

- GetMax — extraction of the maximum value;

- Insert(A) — insertion of a value 𝐴 into the multiset.

Keep in mind that the names of operations differ from the usual ones.


Input

The first line of input contains a single integer 𝑁 (1≤𝑁≤105) — the number of queries to the structure. In the following 𝑁 lines the queries are listed: GetMin, GetMax, Insert(A) — extraction of the minimum, extraction of the maximim, insertion of a value 𝐴 (1≤𝐴≤231−1).


The queries are correct, so no operation of extraction is performed over an empty set.

Output

For ever GetMin and GetMax query print the extracted value.
