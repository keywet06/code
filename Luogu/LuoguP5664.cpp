#include <bits/stdc++.h>
const int N = 105;
const int M = 2005;
const long long mod = 998244353;
int n, m;
long long ans;
long long sum[N];
long long a[N][M];
long long dp[N][N * 2];
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) std::cin >> a[i][j], sum[i] += a[i][j];
        sum[i] %= mod;
    }
    ans = 1;
    for (int i = 1; i <= n; ++i) ans = ans * (sum[i] + 1) % mod;
    --ans;
    dp[0][N] = 1;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = N - j; k <= N + j; ++k) {
                dp[j][k] = (dp[j - 1][k - 1] * a[j][i] % mod + dp[j - 1][k] +
                            dp[j - 1][k + 1] * (sum[j] - a[j][i]) % mod) %
                           mod;
            }
        }
        for (int j = N + 1; j <= N + n; ++j) ans -= dp[n][j];
        ans = (ans % mod + mod) % mod;
    }
    std::cout << ans << std::endl;
    return 0;
}