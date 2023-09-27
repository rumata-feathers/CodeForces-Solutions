# D. Decrease Key

## url: https://codeforces.com/group/PVbQ8eK2T4/contest/347382/problem/D

### D. Decrease Key

time limit per test1.1 seconds

memory limit per test256 megabytes

inputstandard input

outputstandard output


Implement a binary heap.

You need to process queries of the following types:

- insert x — insert an integer 𝑥 into the heap;

- getMin — print the value of the minimum element in the heap (it is guaranteed that the heap is not empty);
- extractMin — remove the minimum element from the heap without printing it (it is guaranteed that the heap is not empty);
- decreaseKey i Δ — decrease the value, which has been inserted on the 𝑖-th query, by an integer Δ≥0 (it is guaranteed that the 𝑖-th query has been performed earlier, it has been an insert query and the inserted value is still in the heap). Please be careful, the 𝑖-th query is taken among all queries, not only insert-type queries.

You may assume that all the elements stored in the heap at any particular moment of time are pairwise distinct and the number of these elements does not exceed 105.


Input

The first line contains a single number 𝑞 (1≤𝑞≤106) representing the number of queries.


The following 𝑞 lines describe the queries in the format stated above. The inserted values 𝑥 and modifications Δ belong to the segment [−109,109] and Δ≥0.


Output

For every query of type getMin print the answer on a separate line.
