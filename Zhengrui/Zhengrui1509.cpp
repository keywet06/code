#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
const int N = 10101;
const int M = 515;
const int mod = 998244353;
std::vector<int> g[N];
int n, ans, K;
int sz[N];
int tmp[M], tmq[M];
int dp[N][M], dq[N][M];
void dfs(int x, int fa = -1) {
    dp[x][0] = 1;
    dq[x][1] = 1;
    sz[x] = 1;
    for (int i : g[x])
        if (i != fa) {
            dfs(i, x);
            for (int j = 0; j <= sz[x]; ++j) {
                for (int k = 0; k <= sz[i] && j + k <= K; ++k) {
                    tmp[j + k] =
                        (tmp[j + k] + (long long)dp[x][j] * dp[i][k]) % mod;
                    tmq[j + k] = (tmq[j + k] + (long long)dp[x][j] * dq[i][k] +
                                  (long long)dq[x][j] * dp[i][k]) %
                                 mod;
                }
            }
            sz[x] = std::min(K, sz[x] + sz[i]);
            for (int j = 0; j <= sz[x]; ++j) {
                dp[x][j] = tmp[j];
                dq[x][j] = tmq[j];
                tmp[j] = tmq[j] = 0;
            }
        }
    for (int j = 1; j <= sz[x]; ++j) dp[x][j] = dq[x][j];
    dp[x][1] = (dp[x][1] + mod - 1) % mod;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cin >> n >> K;
    for (int i = 1; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs(1);
    for (int i = 0; i <= K; ++i) ans = (ans + dp[1][i]) % mod;
    std::cout << ans << '\n';
    return 0;
}