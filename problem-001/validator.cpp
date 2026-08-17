// validator.cpp
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    
    int t = inf.readInt(1, 10000, "t");
    inf.readEoln();
    
    int sum_n = 0, sum_m = 0;
    
    for (int i = 0; i < t; i++) {
        int n = inf.readInt(1, 100000, "n");
        inf.readSpace();
        int m = inf.readInt(0, 200000, "m");
        inf.readEoln();
        
        sum_n += n;
        sum_m += m;
        ensuref(sum_n <= 200000, "Sum of n exceeds 2 * 10^5 limit");
        ensuref(sum_m <= 200000, "Sum of m exceeds 2 * 10^5 limit");

        string c = inf.readToken(format("[a-z]{%d}", n), "c");
        inf.readEoln();
        
        string p = inf.readToken("[a-z]{1,20}", "p");
        inf.readEoln();

        vector<vector<int>> adj(n + 1);
        vector<int> in_degree(n + 1, 0), out_degree(n + 1, 0);

        for (int j = 0; j < m; j++) {
            int u = inf.readInt(1, n, "u");
            inf.readSpace();
            int v = inf.readInt(1, n, "v");
            inf.readEoln();
            
            ensuref(u != v, "Self loops are not allowed");
            adj[u].push_back(v);
            out_degree[u]++;
            in_degree[v]++;
        }
        
        ensuref(in_degree[1] == 0, "Vertex 1 must have no incoming edges");

        // Cycle detection using Kahn's Algorithm
        queue<int> q;
        for(int j = 1; j <= n; j++) {
            if(in_degree[j] == 0) q.push(j);
        }
        
        int visited_count = 0;
        while(!q.empty()) {
            int u = q.front(); 
            q.pop();
            visited_count++;
            for(int v : adj[u]) {
                if(--in_degree[v] == 0) q.push(v);
            }
        }
        ensuref(visited_count == n, "Graph contains a cycle, it must be a DAG");

        // Ensure there is at least one valid path from vertex 1 to any sink
        vector<bool> vis(n + 1, false);
        queue<int> q2;
        q2.push(1);
        vis[1] = true;
        bool reaches_sink = false;
        
        while(!q2.empty()) {
            int u = q2.front(); 
            q2.pop();
            
            if(out_degree[u] == 0) {
                reaches_sink = true;
            }
            
            for(int v : adj[u]) {
                if(!vis[v]) {
                    vis[v] = true;
                    q2.push(v);
                }
            }
        }
        ensuref(reaches_sink, "Vertex 1 must be able to reach at least one sink vertex");
    }
    
    inf.readEof();
    return 0;
}