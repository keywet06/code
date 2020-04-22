#include <bits/stdc++.h>
const int N = 20;
const int M = 1e8 + 7;
int n, m;
int a[N * N], b[N * N], c[N * N], d[N * N];
int dp[2][1 << N];
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < m; j++) {
            scanf("%d", &b[i * m + j]);
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &a[i * m + j]);
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m - 1; j++) {
            c[i * m + j] = a[i * m + j] & b[i * m + j - m + 1];
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            d[i * m + j] = a[i * m + j] & b[i * m + j];
        }
    }
    dp[1][(1 << m) - 1] = 1;
    int p = m - 1;
    for (int j = 0; j < n * m; j++) {
        int t = j & 1;
        memset(dp[t], 0, sizeof(dp[t]));
        for (int i = 0; i < 1 << m; i++)
            if (dp[t ^ 1][i]) {
                dp[t ^ 1][i] %= M;
                dp[t][i >> 1] += dp[t ^ 1][i];
                if (a[j] && !(i & 1)) {
                    dp[t][(i >> 1) | (1 << p)] += dp[t ^ 1][i];
                }
                if (b[j] && !(i >> p)) {
                    dp[t][((i | (1 << p)) >> 1) | (1 << p)] += dp[t ^ 1][i];
                }
                if (c[j] && !(i & 2) && !(i & 1)) {
                    dp[t][(i >> 1) | (1 << p) | 1] += dp[t ^ 1][i];
                }
                if (d[j] && !(i & 1) && !(i >> p)) {
                    dp[t][((i | (1 << p)) >> 1) | (1 << p)] += dp[t ^ 1][i];
                }
            }
    }
    int ans = 0;
    for (int i = 0; i < 1 << m; i++) {
        (ans += dp[(n * m - 1) & 1][i]) %= M;
    }
    printf("%d\n", ans);
}
