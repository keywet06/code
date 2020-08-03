#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
const int C = 2;
const int N = 10005;
const int K = 505;
const int mod = 998244353;
int n, k, x, y;
long long ans;
long long t[C][K];
long long dp[N][C][K];
std::vector<int> to[N];
inline void dfs(int u, int f) {
    register int i, j, flag = 1;
    for (auto v : to[u]) {
        if (v == f) continue;
        dfs(v, u);
        for (j = 1; j <= k; ++j) {
            t[0][j] = dp[u][0][j];
            t[1][j] = dp[u][1][j];
            dp[u][0][j] = dp[u][1][j] = 0;
        }
        for (i = 1; i <= k; ++i) {
            t[0][0] = 1;
            dp[u][0][i] = t[0][i] + dp[v][1][i];
            dp[u][1][i] = t[1][i] + dp[v][1][i] + t[0][i - 1];
            for (j = 1; j < k; ++j) {
                dp[u][0][i] += t[0][j] * dp[v][1][i - j] % mod;
                dp[u][1][i] += t[0][j] * dp[v][1][i - j] % mod;
                dp[u][1][i] += t[1][j] * dp[v][1][i - j] % mod;
            }
            dp[u][0][i] %= mod;
            dp[u][1][i] %= mod;
        }
    }
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> k;
    for (int i = 1; i < n; ++i) {
        std::cin >> x >> y;
        to[x].push_back(y);
        to[y].push_back(x);
    }
    dfs(1, 1);
    ans = 1;
    for (int i = 1; i <= k; ++i) {
        ans += dp[1][1][i];
    }
    std::cout << ans % mod << std::endl;
    return 0;
}