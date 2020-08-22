#include <bits/stdc++.h>
#define mod 998244353
using namespace std;
long long kasumi(long long a, long long b) {
    long long ans = 1;
    while (b) {
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}
long long dp[2][20000][12];
int p[2000];
int n, m, k, pre = 0, now = 1;

int main() {
    scanf("%d%d%d", &n, &k, &m);
    k = n - k + 1;
    now = 1;
    for (int i = 1; i <= n; i++) scanf("%d", &p[i]);
    dp[0][0][0] = 1;
    now = 1, pre = 0;
    for (int i = 1; i <= n; i++) {
        dp[now][0][0] = 1;
        for (int j = 0; j <= m; j++) {
            for (int h = 0; h <= k; h++) {
                dp[now][j][h] = dp[pre][j][h];
                if (j >= p[i] && h != 0) {
                    dp[now][j][h] =
                        (dp[now][j][h] + (dp[pre][j - p[i]][h - 1] -
                                          dp[pre][j - p[i]][h] + mod) %
                                             mod) %
                        mod;
                }
            }
        }
        now ^= 1, pre ^= 1;
    }
    long long ans = 0;
    for (int i = 1; i <= m; i++) {
        ans += dp[pre][i][k] * kasumi(i, mod - 2) % mod;
        ans %= mod;
    }
    printf("%lld\n", ans * m % mod);
}