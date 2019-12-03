#include <bits/stdc++.h>
const int C = 63;
const int N = 300005;
int n, t;
int p[C];
long long s, x, ans;
long long dp[C][N];
int main() {
    scanf("%d %lld", &n, &s);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &x);
        for (int j = 0; j < C; ++j) {
            p[j] += (x >> j) & 1;
        }
    }
    memset(dp, 63, sizeof(dp));
    dp[C - 1][0] = 0;
    for (int i = C - 2; i >= 0; --i) {
        for (int j = 0; j <= n; ++j) {
            t = j * 2 + ((s >> i) & 1) - p[i];
            if (t <= n && t >= 0) {
                dp[i][t] = std::min(dp[i][t], dp[i + 1][j]);
            }
            t = j * 2 + ((s >> i) & 1) - n + p[i];
            if (t <= n && t >= 0) {
                dp[i][t] = std::min(dp[i][t], dp[i + 1][j] + (1ll << i));
            }
        }
    }
    printf("%lld\n", dp[0][0] > (1ll << 61) ? -1 : dp[0][0]);
    return 0;
}