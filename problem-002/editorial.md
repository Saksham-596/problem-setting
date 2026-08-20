# Editorial: The Bipartite Illusion

**Prerequisites:** Graph Theory, Bipartite Graphs, Breadth-First Search (BFS) / Depth-First Search (DFS)

### The Core Observation

The problem allows us to swap any two tokens if there is an **even walk** between them. Because a walk allows us to repeat edges and vertices, we should immediately think about the **parity** of path lengths in a graph. 

When dealing with path parity in connected graphs, the most important property to check is whether the graph is **Bipartite** or not. 

Let's divide the problem into two distinct cases based on the graph's structure.

#### Case 1: The Graph is NOT Bipartite (Contains an Odd Cycle)
If a connected graph is not bipartite, it means it contains at least one cycle with an odd number of edges. 

How does this affect our walks? Suppose the shortest path between two vertices $u$ and $v$ has an **odd** length. Because we can repeat edges, we can construct an even walk between them by doing the following:
1. Walk from $u$ to the odd cycle.
2. Traverse the entire odd cycle (this adds an odd number of edges to our walk length).
3. Walk back to $v$.

Mathematically, `Odd Path + Odd Cycle = Even Walk`. 
Therefore, in a non-bipartite graph, there is an even walk between **every single pair of vertices**. This means we can swap any two tokens in the graph without restrictions. The answer will always be **`YES`**.

#### Case 2: The Graph IS Bipartite (No Odd Cycles)
If the graph is bipartite, we can color its vertices using exactly two colors (let's call them $0$ and $1$) such that no two adjacent vertices have the same color.

In a bipartite graph, the parity of a walk is strictly determined by the colors of its endpoints:
* A walk between two vertices of the **same color** will ALWAYS be **even**.
* A walk between two vertices of **different colors** will ALWAYS be **odd**.

Because we can only swap tokens using even walks, a token on a color $0$ vertex can *only* ever be swapped with a token on another color $0$ vertex. It is physically impossible for a token to cross over to a different color.

Thus, the problem reduces to a simple check: 
For every token $P_i$, its current vertex must have the exact same color as its target vertex $i$. If every token belongs to the same color group as its target destination, we can sort them. If even one token is mismatched, it can never reach its destination, and the answer is **`NO`**.

### The Algorithm

1. Run a standard BFS or DFS starting from vertex $1$ to color the graph with $0$s and $1$s.
2. During the traversal, if you find an edge connecting two vertices of the same color, flag the graph as `is_bipartite = false`.
3. If `is_bipartite` is `false`, immediately output `YES`.
4. If `is_bipartite` is `true`, loop through all vertices from $1$ to $N$. Check if `color[i] == color[P[i]]` for all $i$.
5. If all colors match, output `YES`. Otherwise, output `NO`.

### Complexity

* **Time Complexity:** $O(N + M)$ per test case. We traverse the graph exactly once using BFS/DFS, and then do a single $O(N)$ pass to verify the colors.
* **Space/Memory Complexity:** $O(N + M)$ to store the adjacency list and the color array.

This comfortably passes within the 1.0-second time limit.