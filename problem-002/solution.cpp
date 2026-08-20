#include <iostream>
#include <vector>

using namespace std;

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

    vector<int> color(n + 1, -1);
    bool is_bipartite = true;

    // Since the graph is guaranteed to be connected, 
    // a single BFS from node 1 will visit all nodes.
    vector<int> q;
    q.push_back(1);
    color[1] = 0;

    int head = 0;
    while (head < (int)q.size()) {
        int u = q[head++];
        for (int v : adj[u]) {
            if (color[v] == -1) {
                color[v] = 1 - color[u];
                q.push_back(v);
            } else if (color[v] == color[u]) {
                is_bipartite = false; // We found an odd cycle
            }
        }
    }

    // Case 1: Graph has an odd cycle. All even walks are possible.
    if (!is_bipartite) {
        cout << "YES\n";
        return;
    }

    // Case 2: Graph is bipartite. Tokens can only swap with other tokens 
    // that belong to the exact same color partition (0 or 1).
    bool possible = true;
    for (int i = 1; i <= n; i++) {
        // Token 'p[i]' is currently at color 'color[i]'.
        // It needs to go to vertex 'p[i]', which has color 'color[p[i]]'.
        if (color[i] != color[p[i]]) {
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
    // Fast I/O
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