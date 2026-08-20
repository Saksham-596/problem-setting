#include "testlib.h"
#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

// Helper to color a tree to establish Bipartite Left/Right sets
void color_tree(int n, const vector<vector<int>>& adj, vector<int>& color) {
    color.assign(n + 1, -1);
    queue<int> q;
    q.push(1);
    color[1] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (color[v] == -1) {
                color[v] = 1 - color[u];
                q.push(v);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    // Initialize testlib generator with command line arguments (seed, etc.)
    registerGen(argc, argv, 1);

    // Command line arguments: <num_testcases> <sum_n> <sum_m>
    int t = opt<int>(1);
    int sum_n = opt<int>(2);
    int sum_m = opt<int>(3);

    // Randomly distribute N across T test cases ensuring sum is exactly sum_n
    vector<int> n_arr = rnd.partition(t, sum_n, 3); 
    
    // Distribute remaining extra edges (M - N + 1) across the test cases
    int extra_edges_total = sum_m - sum_n + t;
    vector<int> extra_arr = rnd.partition(t, extra_edges_total, 0);

    cout << t << "\n";

    for (int i = 0; i < t; i++) {
        int n = n_arr[i];
        int m = n - 1 + extra_arr[i];

        // Ensure we don't request more edges than a graph can hold
        long long max_edges = (long long)n * (n - 1) / 2;
        if (m > max_edges) m = max_edges;

        // Randomly pick the type of test case
        // 0: Bipartite (YES answer)
        // 1: Bipartite (NO answer)
        // 2: Non-Bipartite (YES answer)
        int type = rnd.next(0, 2);

        // 1. Generate a random Tree (which is naturally bipartite)
        vector<pair<int, int>> edges;
        vector<vector<int>> adj(n + 1);
        for (int v = 2; v <= n; v++) {
            int u = rnd.next(1, v - 1);
            edges.push_back({u, v});
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // Color the tree to get Left and Right partitions
        vector<int> color;
        color_tree(n, adj, color);

        vector<int> L, R;
        for (int v = 1; v <= n; v++) {
            if (color[v] == 0) L.push_back(v);
            else R.push_back(v);
        }

        set<pair<int, int>> existing_edges;
        for (auto e : edges) {
            existing_edges.insert({min(e.first, e.second), max(e.first, e.second)});
        }

        // 2. Add extra edges based on the test case type
        int extra_needed = m - (n - 1);
        if (type == 2 && extra_needed > 0) {
            // Force an odd cycle by connecting two nodes of the SAME color
            bool added = false;
            for(int attempts = 0; attempts < 20 && !added; attempts++) {
                vector<int>& target_set = (L.size() >= 2 && rnd.next(0, 1)) ? L : R;
                if (target_set.size() < 2) target_set = (L.size() >= 2) ? L : R;
                
                if (target_set.size() >= 2) {
                    int u = target_set[rnd.next(int(target_set.size()))];
                    int v = target_set[rnd.next(int(target_set.size()))];
                    if (u != v) {
                        int mn = min(u, v), mx = max(u, v);
                        if (!existing_edges.count({mn, mx})) {
                            existing_edges.insert({mn, mx});
                            edges.push_back({mn, mx});
                            added = true;
                            extra_needed--;
                        }
                    }
                }
            }
        }

        // Add remaining extra edges safely
        while (extra_needed > 0) {
            int u, v;
            if (type == 0 || type == 1) {
                // Must remain bipartite, only connect L to R
                u = L[rnd.next(int(L.size()))];
                v = R[rnd.next(int(R.size()))];
            } else {
                // Non-bipartite, connect anything
                u = rnd.next(1, n);
                v = rnd.next(1, n);
            }

            if (u != v) {
                int mn = min(u, v), mx = max(u, v);
                if (!existing_edges.count({mn, mx})) {
                    existing_edges.insert({mn, mx});
                    edges.push_back({mn, mx});
                    extra_needed--;
                }
            }
        }

        // 3. Generate the Permutation P
        vector<int> P(n + 1);
        if (type == 0) {
            // Bipartite YES: Shuffle L internally, Shuffle R internally
            vector<int> pL = L, pR = R;
            shuffle(pL.begin(), pL.end());
            shuffle(pR.begin(), pR.end());
            for (size_t j = 0; j < L.size(); j++) P[L[j]] = pL[j];
            for (size_t j = 0; j < R.size(); j++) P[R[j]] = pR[j];
        } else if (type == 1) {
            // Bipartite NO: Same as above, but force exactly one swap across the boundary
            vector<int> pL = L, pR = R;
            shuffle(pL.begin(), pL.end());
            shuffle(pR.begin(), pR.end());
            for (size_t j = 0; j < L.size(); j++) P[L[j]] = pL[j];
            for (size_t j = 0; j < R.size(); j++) P[R[j]] = pR[j];
            
            if (!L.empty() && !R.empty()) {
                swap(P[L[0]], P[R[0]]);
            }
        } else {
            // Non-bipartite YES: Completely random shuffle, all swaps are valid
            for (int j = 1; j <= n; j++) P[j] = j;
            shuffle(P.begin() + 1, P.end());
        }

        // 4. Output the testcase
        cout << n << " " << edges.size() << "\n";
        
        for (int j = 1; j <= n; j++) {
            cout << P[j] << (j == n ? "" : " ");
        }
        cout << "\n";

        // Shuffle edges and their directions so solutions can't assume a tree-like order
        shuffle(edges.begin(), edges.end());
        for (auto e : edges) {
            if (rnd.next(0, 1)) swap(e.first, e.second);
            cout << e.first << " " << e.second << "\n";
        }
    }

    return 0;
}