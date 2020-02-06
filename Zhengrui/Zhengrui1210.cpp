#include <bits/stdc++.h>
const int N = 5000;
const int Np = N + 5;
const int mod = 1e9 + 7;
int c, n, m, L, ans, cnt;
int v[Np], fa[Np], q[Np], e[Np];
int dp[Np][Np];
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m >> L;
    for (int i = 2; i <= n; ++i) {
        std::cin >> fa[i];
    }
    for (int i = 1; i <= n; ++i) {
        std::cin >> v[i];
    }
    for (int i = 1; i <= n; ++i) {
        dp[i][L + 1] = 1;
    }
    for (int i = n; i; --i) {
        (dp[i][v[i]] += dp[i][v[i] + 1]) %= mod;
        for (int j = 1; j <= L; ++j) {
            (dp[fa[i]][j] += dp[i][j]) %= mod;
        }
    }
    for (int i = 1; i <= m; ++i) {
        c = (i - 1) % n + 1;
        for (int j = c; j; j = fa[j]) {
            (dp[j][v[j]] += mod - dp[j][v[j] + 1]) %= mod;
            for (int k = 1; k <= L; ++k) {
                (dp[fa[j]][k] += mod - dp[j][k]) %= mod;
            }
        }
        std::cin >> v[c];
        for (int j = c; j; j = fa[j]) {
            (dp[j][v[j]] += dp[j][v[j] + 1]) %= mod;
            for (int k = 1; k <= L; ++k) {
                (dp[fa[j]][k] += dp[j][k]) %= mod;
            }
        }
        (ans += 1ll * i * dp[1][1]) %= mod;
    }
    std::cout << ans << std::endl;
    return 0;
}