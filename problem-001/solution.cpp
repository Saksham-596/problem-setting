#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <algorithm>
#include <array>

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

void solve() {
    int n, m;
    cin >> n >> m;
    string c;
    cin >> c;
    string P;
    cin >> P;
    int k = P.length();
    
    vector<vector<int>> adj(n + 1);
    vector<int> in_degree(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        in_degree[v]++;
    }
    
    // KMP prefix array construction
    vector<int> pi(k);
    for (int i = 1; i < k; i++) {
        int j = pi[i - 1];
        while (j > 0 && P[i] != P[j]) {
            j = pi[j - 1];
        }
        if (P[i] == P[j]) {
            j++;
        }
        pi[i] = j;
    }
    
    // Construct DFA Next-State mappings
    vector<array<int, 26>> next_state(k + 1);
    for (int i = 0; i <= k; ++i) {
        for (char ch = 'a'; ch <= 'z'; ++ch) {
            if (i == k) {
                next_state[i][ch - 'a'] = k; // Absorbing match state
            } else {
                int j = i;
                while (j > 0 && P[j] != ch) {
                    j = pi[j - 1];
                }
                if (P[j] == ch) {
                    j++;
                }
                next_state[i][ch - 'a'] = j;
            }
        }
    }
    
    // Topological sort (Kahn's algorithm)
    queue<int> q;
    for (int u = 1; u <= n; ++u) {
        if (in_degree[u] == 0) {
            q.push(u);
        }
    }
    
    vector<int> topo;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        topo.push_back(u);
        for (int v : adj[u]) {
            if (--in_degree[v] == 0) {
                q.push(v);
            }
        }
    }
    
    vector<int> tot(n + 1, 0);
    vector<array<long long, 25>> dp(n + 1);
    
    // DP evaluated dynamically traversing via backward topological ordering
    for (int i = (int)topo.size() - 1; i >= 0; --i) {
        int u = topo[i];
        if (adj[u].empty()) {  // Vertex with no outgoing edges (sink)
            tot[u] = 1;
            for (int s = 0; s <= k; ++s) {
                dp[u][s] = (s == k ? 1 : 0);
            }
        } else {
            for (int s = 0; s <= k; ++s) {
                dp[u][s] = 0;
            }
            for (int v : adj[u]) {
                tot[u] = (tot[u] + tot[v]) % MOD;
                for (int s = 0; s <= k; ++s) {
                    int nxt = next_state[s][c[v - 1] - 'a']; // Using c[v-1] accommodating 0-index character extraction indexing
                    dp[u][s] = (dp[u][s] + dp[v][nxt]) % MOD;
                }
            }
        }
    }
    
    // Obtain configurations relative to initially tracking vertex 1 string extraction mapping
    int start_state = next_state[0][c[0] - 'a'];
    long long ans = (1LL * dp[1][start_state] * modInverse(tot[1])) % MOD;
    
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