#include "testlib.h"
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <cstdlib>

using namespace std;

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
    // Initialize testlib generator
    registerGen(argc, argv, 1);

    // Bypassing testlib's opt<int> to avoid version shift bugs.
    // argv[0] = ./gen, argv[1] = SEED
    int t = atoi(argv[2]);
    int sum_n = atoi(argv[3]);
    int sum_m = atoi(argv[4]);

    // ==============================================================
    // STRICT MATHEMATICAL CLAMPS (Prevents testlib from crashing)
    // ==============================================================
    if (t * 3 > sum_n) {
        t = sum_n / 3;
        if (t == 0) { t = 1; sum_n = 3; }
    }

    int extra_edges_total = sum_m - sum_n + t;
    if (extra_edges_total < 0) {
        extra_edges_total = 0;
    }
    // ==============================================================

    // If it passes the clamps above, these partitions are mathematically guaranteed to never crash.
    vector<int> n_arr = rnd.partition(t, sum_n, 3); 
    vector<int> extra_arr = rnd.partition(t, extra_edges_total, 0);

    cout << t << "\n";

    for (int i = 0; i < t; i++) {
        int n = n_arr[i];
        int m = n - 1 + extra_arr[i];

        long long max_edges = (long long)n * (n - 1) / 2;
        if (m > max_edges) m = max_edges;

        int type = rnd.next(0, 2);

        vector<pair<int, int>> edges;
        vector<vector<int>> adj(n + 1);
        for (int v = 2; v <= n; v++) {
            int u = rnd.next(1, v - 1);
            edges.push_back({u, v});
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

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

        int extra_needed = m - (n - 1);
        if (type == 2 && extra_needed > 0) {
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

        // ---------------------------------------------------------
        // FIX: Added 'failed_attempts' to prevent infinite looping
        // when the bipartite graph is already fully dense!
        // ---------------------------------------------------------
        int failed_attempts = 0;
        while (extra_needed > 0 && failed_attempts < 50) {
            int u = rnd.next(1, n), v = rnd.next(1, n);
            if (type == 0 || type == 1) {
                if (!L.empty() && !R.empty()) {
                    u = L[rnd.next(int(L.size()))];
                    v = R[rnd.next(int(R.size()))];
                }
            } 

            if (u != v) {
                int mn = min(u, v), mx = max(u, v);
                if (!existing_edges.count({mn, mx})) {
                    existing_edges.insert({mn, mx});
                    edges.push_back({mn, mx});
                    extra_needed--;
                    failed_attempts = 0; // Success! Reset frustration counter
                } else {
                    failed_attempts++; // Failed to find a new edge
                }
            } else {
                failed_attempts++; 
            }
        }

        vector<int> P(n + 1);
        if (type == 0) {
            vector<int> pL = L, pR = R;
            shuffle(pL.begin(), pL.end());
            shuffle(pR.begin(), pR.end());
            for (size_t j = 0; j < L.size(); j++) P[L[j]] = pL[j];
            for (size_t j = 0; j < R.size(); j++) P[R[j]] = pR[j];
        } else if (type == 1) {
            vector<int> pL = L, pR = R;
            shuffle(pL.begin(), pL.end());
            shuffle(pR.begin(), pR.end());
            for (size_t j = 0; j < L.size(); j++) P[L[j]] = pL[j];
            for (size_t j = 0; j < R.size(); j++) P[R[j]] = pR[j];
            if (!L.empty() && !R.empty()) swap(P[L[0]], P[R[0]]);
        } else {
            for (int j = 1; j <= n; j++) P[j] = j;
            shuffle(P.begin() + 1, P.end());
        }

        cout << n << " " << edges.size() << "\n";
        for (int j = 1; j <= n; j++) cout << P[j] << (j == n ? "" : " ");
        cout << "\n";

        shuffle(edges.begin(), edges.end());
        for (auto e : edges) {
            if (rnd.next(0, 1)) swap(e.first, e.second);
            cout << e.first << " " << e.second << "\n";
        }
    }

    return 0;
}