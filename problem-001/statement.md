# Random Path Pattern

You are given a directed acyclic graph (DAG) consisting of `n` vertices and `m` directed edges.

Each vertex `i` has a single lowercase English letter `c_i` assigned to it.

Let `S` be the set of all valid paths that start at vertex `1` and end at any sink vertex. A sink vertex is a vertex whose out-degree is `0`.

It is guaranteed that at least one such path exists, and vertex `1` has no incoming edges.

The generator chooses **one path uniformly at random from `S`**.

As the generator traverses the chosen path, it concatenates the characters written on the visited vertices in order, forming a string.

For example, if the chosen path is:

```text
1 → 3 → 5 → 7
```

and the characters are:

```text
c₁ = a
c₃ = b
c₅ = a
c₇ = c
```

then the generated string is:

```text
abac
```

You are also given a pattern string `P`.

Your task is to determine the probability that `P` occurs as a **contiguous substring** of the generated string.

Print the answer modulo `998244353`.

More formally, if:

- `T` is the total number of valid paths from vertex `1` to a sink;
- `G` is the number of those paths whose generated string contains `P` as a substring;

then the required probability is:

$begin:math:display$
\\frac\{G\}\{T\}\.
$end:math:display$

It is guaranteed that the denominator is non-zero modulo `998244353`.

## Important

The generator chooses **complete paths uniformly**.

It does **not** choose each outgoing edge uniformly and independently.

## Input

The first line contains a single integer `t` (`1 ≤ t ≤ 10^4`) — the number of test cases.

For each test case:

The first line contains two integers `n` and `m`:

```text
1 ≤ n ≤ 10^5
0 ≤ m ≤ 2 · 10^5
```

The second line contains a string `c` of length `n`, consisting of lowercase English letters.

The `i`-th character of `c` is the character assigned to vertex `i`.

The third line contains the pattern string `P`:

```text
1 ≤ |P| ≤ 20
```

`P` consists only of lowercase English letters.

The next `m` lines each contain two integers `u` and `v`:

```text
1 ≤ u, v ≤ n
u ≠ v
```

representing a directed edge from vertex `u` to vertex `v`.

It is guaranteed that:

- The graph is a DAG.
- Vertex `1` has no incoming edges.
- At least one path starts at vertex `1` and ends at a sink.

The sum of `n` over all test cases does not exceed `2 · 10^5`.

The sum of `m` over all test cases does not exceed `2 · 10^5`.

## Output

For each test case, output a single integer — the probability that `P` occurs as a contiguous substring of the generated string, modulo `998244353`.

If the probability is represented as the irreducible fraction

$begin:math:display$
\\frac\{p\}\{q\}\,
$end:math:display$

the required output is:

$begin:math:display$
p \\cdot q\^\{\-1\} \\pmod\{998244353\}\.
$end:math:display$

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

## Explanation

In the first test case, there are two valid paths:

```text
1 → 2 → 4 → 5
1 → 3 → 4 → 5
```

They are chosen with equal probability.

The corresponding generated strings are:

```text
ababa
aabba
```

The pattern is:

```text
aba
```

It occurs in the first string but not in the second.

Therefore, the probability is:

$begin:math:display$
\\frac\{1\}\{2\}\.
$end:math:display$

Since

$begin:math:display$
2\^\{\-1\} \\equiv 499122177 \\pmod\{998244353\}\,
$end:math:display$

the answer is:

```text
499122177
```

In the second test case, the two valid paths are:

```text
1 → 2
1 → 3
```

Their generated strings are:

```text
xy
xz
```

The pattern is:

```text
y
```

It occurs in exactly one of the two strings, so again the probability is `1/2`.