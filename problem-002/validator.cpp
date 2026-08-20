#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

// Disjoint Set Union to efficiently verify graph connectivity
struct DSU {
    vector<int> parent;
    int comps;
    DSU(int n) {
        parent.resize(n + 1);
        for (int i = 1; i <= n; i++) parent[i] = i;
        comps = n;
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
            comps--;
        }
    }
};

int main(int argc, char* argv[]) {
    // Initialize standard Polygon validator
    registerValidation(argc, argv);

    // Read the number of test cases
    int t = inf.readInt(1, 10000, "t");
    inf.readEoln();

    int sum_n = 0;
    int sum_m = 0;

    for (int testCase = 1; testCase <= t; testCase++) {
        // 1. Read N and M
        int n = inf.readInt(3, 200000, "n");
        inf.readSpace();
        int m = inf.readInt(n - 1, 200000, "m");
        inf.readEoln();

        // Check global sum constraints
        sum_n += n;
        sum_m += m;
        ensuref(sum_n <= 200000, "Sum of N exceeded 200,000 on test case %d", testCase);
        ensuref(sum_m <= 200000, "Sum of M exceeded 200,000 on test case %d", testCase);

        // 2. Read the Permutation array P
        vector<bool> used(n + 1, false);
        for (int i = 1; i <= n; i++) {
            int p_val = inf.readInt(1, n, "P_i");
            ensuref(!used[p_val], "Permutation has duplicate element %d in testcase %d", p_val, testCase);
            used[p_val] = true;
            
            if (i < n) {
                inf.readSpace();
            }
        }
        inf.readEoln();

        // 3. Read the edges and validate graph properties
        set<pair<int, int>> edges;
        DSU dsu(n);

        for (int i = 1; i <= m; i++) {
            int u = inf.readInt(1, n, "u");
            inf.readSpace();
            int v = inf.readInt(1, n, "v");
            inf.readEoln();

            // Check for self-loops
            ensuref(u != v, "Self-loop detected at node %d in testcase %d", u, testCase);
            
            // Check for multiple edges
            int mn = min(u, v);
            int mx = max(u, v);
            ensuref(edges.find({mn, mx}) == edges.end(), "Multiple edges detected between %d and %d in testcase %d", mn, mx, testCase);
            
            edges.insert({mn, mx});
            dsu.unite(u, v);
        }

        // 4. Check connectivity
        ensuref(dsu.comps == 1, "Graph is disconnected in testcase %d", testCase);
    }

    // Ensure there are no extra trailing characters or whitespace at the end of the file
    inf.readEof();
    
    return 0;
}