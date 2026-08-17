// generator.cpp
#include "testlib.h"
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    // Number of test cases
    int t = rnd.next(1, 15);
    cout << t << "\n";
    
    int rem_n = 200000;
    int rem_m = 200000;
    
    for (int i = 0; i < t; i++) {
        // 1. Determine constraints for this test case
        int max_n_allowed = min(rem_n, 100000);
        if (max_n_allowed < 1) max_n_allowed = 1;
        
        int n = (i == t - 1) ? max_n_allowed : rnd.next(1, max_n_allowed);
        
        long long max_possible_edges = 1LL * n * (n - 1) / 2;
        int max_m_allowed = min({(long long)rem_m, max_possible_edges, 200000LL});
        int target_m = (i == t - 1) ? max_m_allowed : rnd.next(0, max_m_allowed);

        rem_n -= n;
        
        // 2. Generate vertex characters
        string c = "";
        for(int j = 0; j < n; j++) {
            c += (char)('a' + rnd.next(0, 25));
        }

        // 3. Generate pattern
        int p_len = rnd.next(1, min(20, n + 5)); 
        string p = "";
        for(int j = 0; j < p_len; j++) {
            p += (char)('a' + rnd.next(0, 25));
        }

        // 4. Generate DAG edges
        set<pair<int, int>> edges;
        vector<pair<int, int>> edge_list;
        
        int edge_attempts = 0;
        while((int)edge_list.size() < target_m && edge_attempts < target_m * 5) {
            edge_attempts++;
            int u = rnd.next(1, n - 1);
            int v = rnd.next(u + 1, n); // u < v ensures it's a DAG and 1 has no incoming
            
            if (edges.count({u, v})) continue;
            
            edges.insert({u, v});
            edge_list.push_back({u, v});
        }
        
        int actual_m = edge_list.size(); // Lock in the exact number of valid edges
        rem_m -= actual_m;

        // Ensure vertex 1 connects to something if n > 1 and actual_m > 0
        if (n > 1 && actual_m > 0) {
            bool one_has_out = false;
            for (auto e : edge_list) {
                if (e.first == 1) one_has_out = true;
            }
            if (!one_has_out && !edge_list.empty()) {
                int v = rnd.next(2, n);
                edge_list[0] = {1, v};
            }
        }

        // 5. Print the complete test case in correct order
        cout << n << " " << actual_m << "\n";
        cout << c << "\n";
        cout << p << "\n";

        // Shuffle edge printing order so topological order isn't obvious
        shuffle(edge_list.begin(), edge_list.end());
        for (auto e : edge_list) {
            cout << e.first << " " << e.second << "\n";
        }
    }
    return 0;
}