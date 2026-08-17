// brute.cpp
#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

long long modInverse(long long n) {
    return power(n, MOD - 2);
}

int total_paths = 0;
int successful_paths = 0;
string chars, pattern;
vector<vector<int>> adj;
vector<int> out_degree;

// DFS to exhaustively find all paths (Note: Will TLE on large DAGs, intended for correctness checks)
void dfs(int u, string current_string) {
    current_string += chars[u - 1];
    
    // If it's a sink vertex
    if (out_degree[u] == 0) {
        total_paths = (total_paths + 1) % MOD;
        if (current_string.find(pattern) != string::npos) {
            successful_paths = (successful_paths + 1) % MOD;
        }
        return;
    }
    
    for (int v : adj[u]) {
        dfs(v, current_string);
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    cin >> chars >> pattern;
    
    adj.assign(n + 1, vector<int>());
    out_degree.assign(n + 1, 0);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        out_degree[u]++;
    }
    
    total_paths = 0;
    successful_paths = 0;
    
    dfs(1, "");
    
    long long ans = (1LL * successful_paths * modInverse(total_paths)) % MOD;
    cout << ans << "\n";
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