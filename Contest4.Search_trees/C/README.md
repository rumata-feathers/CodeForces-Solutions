# C. K-th Maximum

## url: https://codeforces.com/group/PVbQ8eK2T4/contest/357142/problem/C\

### C. K-th maximum

time limit per test0.5 seconds

memory limit per test64 megabytes

inputstandard input

outputstandard output


Write a program that implements a data structure that allows you to add and remove elements, and also find the 𝑘-th maximum.



Input

The first line of the input file contains the natural number 𝑛 — the number of commands (𝑛≤100000). The next 𝑛 lines contain one command each. The team is recorded in the form of two numbers 𝑐𝑖 and 𝑘𝑖 — the type and argument of the command, respectively (|𝑘𝑖|≤109).


Supported commands:

- +1 (or just 1): Add an item with key 𝑘𝑖.
- 0: Find and display the 𝑘𝑖-th maximum.
- −1: Remove item with key 𝑘𝑖.

It is guaranteed that in the course of work in the structure it is not required to store elements with equal keys or remove non-existent elements. It is also guaranteed that when requesting the 𝑘𝑖-th maximum, it exists.



Output

For each command of the type 0, a line containing a single number — 𝑘𝑖-th maximum.

