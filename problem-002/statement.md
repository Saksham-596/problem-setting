# The Bipartite Illusion

**Time Limit:** 1.0 second  
**Memory Limit:** 256 megabytes  

### Problem Statement

You are given a connected, unweighted, undirected graph consisting of $N$ vertices and $M$ edges. There are no self-loops and no multiple edges.

Each vertex $i$ contains a token with a value $P_i$. It is guaranteed that the array $P$ is a permutation of the integers from $1$ to $N$.

Your goal is to sort the tokens such that every vertex $i$ contains the token with the value $i$. To achieve this, you can perform the following operation any number of times (possibly zero):

* Choose two vertices $u$ and $v$ such that there exists a **walk of even length** between $u$ and $v$.
* Swap the token at vertex $u$ with the token at vertex $v$. All other tokens remain unaffected.

A **walk** is a sequence of connected vertices and edges. Unlike a simple path, a walk is allowed to visit the same vertex or traverse the same edge multiple times. The length of a walk is the total number of edge traversals.

Determine if it is possible to sort the permutation using the given operation.

### Input

The first line contains a single integer $t$ ($1 \le t \le 10^4$) — the number of test cases. The description of the test cases follows.

The first line of each testcase contains two integers $N$ and $M$ ($3 \le N \le 2 \cdot 10^5$, $N - 1 \le M \le 2 \cdot 10^5$) — the number of vertices and the number of edges in the graph.

The second line of each testcase contains $N$ integers $P_1, P_2, \dots, P_N$ ($1 \le P_i \le N$) — the initial values of the tokens on the vertices.

The following $M$ lines each contain two integers $u$ and $v$ ($1 \le u, v \le N, u \neq v$), representing an undirected edge between vertex $u$ and vertex $v$.

**Constraints:**
* The graph is guaranteed to be connected.
* The sum of $N$ and the sum of $M$ over all test cases do not exceed $2 \cdot 10^5$.

### Output

For each test case, output `YES` if it is possible to sort the permutation, and `NO` otherwise. You can output the answer in any case (upper or lower).

### Example

#### Input
```text
3
4 3
3 2 1 4
1 2
2 3
3 4
4 3
2 1 3 4
1 2
2 3
3 4
3 3
2 3 1
1 2
2 3
3 1
```

#### Output
```text
YES
NO
YES
```

### Note

In the **first test case**, the graph is a line: $1 - 2 - 3 - 4$. The initial tokens are `[3, 2, 1, 4]`. We need to swap the tokens at vertex $1$ and vertex $3$. The path $1 \to 2 \to 3$ has a length of $2$ (which is even). Therefore, we can directly swap the tokens at vertex $1$ and vertex $3$. The tokens become `[1, 2, 3, 4]`, which is sorted. 

In the **second test case**, the graph is the same line, but the tokens are `[2, 1, 3, 4]`. We need to swap the tokens at vertex $1$ and vertex $2$. The direct path $1 \to 2$ has a length of $1$ (odd). Any walk between $1$ and $2$ will always have an odd length (for example, $1 \to 2 \to 3 \to 2$ has a length of $3$). Since no even walk exists between vertex $1$ and vertex $2$, it is impossible to swap them.

In the **third test case**, the graph is a triangle. The initial tokens are `[2, 3, 1]`. We can sort the array by swapping vertex $1$ and vertex $2$, and then swapping vertex $2$ and vertex $3$. Wait, is there an even walk between vertex $1$ and vertex $2$? Yes! We can use the walk $1 \to 3 \to 2$, which has a length of $2$. Because the graph contains an odd cycle, there is an even walk between *any* pair of vertices, meaning we can swap any two tokens we want.