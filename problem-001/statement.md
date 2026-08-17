# Problem Statement

You are given a DAG consisting of $n$ vertices and $m$ edges. Each vertex $i$ has a single lowercase English letter $c_i$ assigned to it.

Let $S$ be the set of all valid paths starting from vertex $1$ and ending at any sink vertex (a vertex with an out-degree of $0$).

It is guaranteed that at least one such path exists, and vertex $1$ has no incoming edges.

The generator chooses a path from $S$ uniformly at random.

As the generator traverses the chosen path, it concatenates the characters $c_i$ of the visited vertices in order, forming a generated string.

Saksham has a specific pattern string $P$.

He wants to know: what is the probability that $P$ occurs as a contiguous substring within the randomly generated string?

Print the probability modulo $998244353$.

## Input

The first line contains a single integer $t$ ($1 \le t \le 10^4$) — the number of test cases.

For each test case:

The first line contains two integers $n$ and $m$ ($1 \le n \le 10^5$, $0 \le m \le 2 \cdot 10^5$) — the number of vertices and edges in the DAG.

The second line contains a string of $n$ lowercase English letters. The $i$-th letter represents $c_i$.

The third line contains the pattern string $P$ ($1 \le |P| \le 20$), consisting of lowercase English letters.

The next $m$ lines each contain two integers $u$ and $v$ ($1 \le u, v \le n$, $u \neq v$), denoting a directed edge from vertex $u$ to vertex $v$.

It is guaranteed that the given graph is a DAG, vertex $1$ has no incoming edges, and the sum of $n$ and sum of $m$ over all test cases do not exceed $2 \cdot 10^5$.

## Output

For each test case, output a single integer — the probability that $P$ is a substring of the generated string, modulo 998244353.

Formally, let $M = 998244353$.

It can be shown that the probability can be expressed as an irreducible fraction $\frac{p}{q}$, where $p$ and $q$ are integers and $q \not\equiv 0 \pmod M$.

Output the integer equal to $p \cdot q^{-1} \bmod M$.

## Example

### Input

```text
2
5 5
ababa
aba
1 2
1 3
2 4
3 4
4 5
3 2
xyz
y
1 2
1 3
```

### Output

```text
499122177
499122177
```