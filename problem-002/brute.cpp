#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Standard Disjoint Set Union (DSU) to group vertices that can swap tokens
struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n + 1);
        for (int i = 1; i <= n; i++) parent[i] = i;
    }
    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
        }
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    DSU dsu(n);

    // BRUTE FORCE: For every node, explore all paths keeping track of parity.
    // Time Complexity: O(N * (N + M)), strictly intended to TLE on large tests.
    for (int start_node = 1; start_node <= n; start_node++) {
        
        // visited[node][parity] : tracks if we can reach 'node' with 'parity' length
        vector<vector<bool>> visited(n + 1, vector<bool>(2, false));
        
        // Queue stores pairs of {current_node, current_path_length_parity}
        queue<pair<int, int>> q;
        
        q.push({start_node, 0});
        visited[start_node][0] = true;

        while (!q.empty()) {
            int u = q.front().first;
            int parity = q.front().second;
            q.pop();

            for (int v : adj[u]) {
                int next_parity = 1 - parity; // Toggle parity (0 to 1, or 1 to 0)
                
                if (!visited[v][next_parity]) {
                    visited[v][next_parity] = true;
                    q.push({v, next_parity});
                }
            }
        }

        // Any node we reached with an EVEN parity (0) can be swapped with 'start_node'
        for (int v = 1; v <= n; v++) {
            if (visited[v][0]) {
                dsu.unite(start_node, v);
            }
        }
    }

    // Verify if every token P[i] can successfully be swapped to its target vertex 'i'
    bool possible = true;
    for (int i = 1; i <= n; i++) {
        // If the current location of the token (i) is not in the same 
        // valid swap group as its required destination (P[i])
        if (dsu.find(i) != dsu.find(p[i])) {
            possible = false;
            break;
        }
    }

    if (possible) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}