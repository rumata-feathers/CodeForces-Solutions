# E. First Elements of a long sequence
## url: https://codeforces.com/group/PVbQ8eK2T4/contest/347382/problem/E

### E. First elements of a long sequence

time limit per test1 second

memory limit per test4 megabytes

inputstandard input

outputstandard output


You are given a sequence of integer numbers of length 𝑛. You are to find its 𝑘 smallest elements.


In order not to read the long sequence, its elements are determined by a formula. Namely, the input contains numbers 𝑎0,𝑥,𝑦. We determine 𝑎𝑖=(𝑥⋅𝑎𝑖−1+𝑦) (mod 2^30). Then the sequence is equal to 𝑎1,𝑎2,…,𝑎𝑛.


Please note the memory limit.


Input

The first line contains 𝑛 and 𝑘 (1≤𝑛≤107,1≤𝑘≤1000).


The second line contains space-separated integers 𝑎0,𝑥,𝑦 (0≤𝑎0,𝑥,𝑦<230).

Output
Print 𝑘 smallest elements of the sequence in non-decreasing order.
