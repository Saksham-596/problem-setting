// generator.cpp
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    // Number of test cases
    int t = rnd.next(1, 15);
    cout << t << "\n";
    
    int rem_n = 200000;
    int rem_m = 200000;
    
    for (int i = 0; i < t; i++) {
        int max_n_allowed = min(rem_n, 100000);
        if (max_n_allowed < 1) max_n_allowed = 1;
        
        // Force the last test case to absorb the remaining N and M to test constraints
        int n = (i == t - 1) ? max_n_allowed : rnd.next(1, max_n_allowed);
        
        long long max_possible_edges = 1LL * n * (n - 1) / 2;
        int max_m_allowed = min({(long long)rem_m, max_possible_edges, 200000LL});
        int m = (i == t - 1) ? max_m_allowed : rnd.next(0, max_m_allowed);

        rem_n -= n;
        rem_m -= m;

        cout << n << " " << m << "\n";
        
        // Generate vertex characters
        string c = "";
        for(int j = 0; j < n; j++) {
            c += (char)('a' + rnd.next(0, 25));
        }
        cout << c << "\n";

        // Generate pattern
        int p_len = rnd.next(1, min(20, n + 5)); 
        string p = "";
        for(int j = 0; j < p_len; j++) {
            p += (char)('a' + rnd.next(0, 25));
        }
        cout << p << "\n";

        // Generate DAG edges
        set<pair<int, int>> edges;
        vector<pair<int, int>> edge_list;
        
        int edge_attempts = 0;
        while(edge_list.size() < m && edge_attempts < m * 5) {
            edge_attempts++;
            int u = rnd.next(1, n - 1);
            int v = rnd.next(u + 1, n); // u < v ensures it's a DAG and 1 has no incoming
            
            if (edges.count({u, v})) continue;
            
            edges.insert({u, v});
            edge_list.push_back({u, v});
        }
        
        // Ensure vertex 1 connects to something if n > 1 and m > 0 (to avoid 0 paths)
        if (n > 1 && m > 0) {
            bool one_has_out = false;
            for (auto e : edge_list) {
                if (e.first == 1) one_has_out = true;
            }
            if (!one_has_out && !edge_list.empty()) {
                int v = rnd.next(2, n);
                edge_list[0] = {1, v};
            }
        }

        // Shuffle edge printing order
        shuffle(edge_list.begin(), edge_list.end());
        for (auto e : edge_list) {
            cout << e.first << " " << e.second << "\n";
        }
    }
    return 0;
}