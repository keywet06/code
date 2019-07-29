#include <bits/stdc++.h>
const int C = 305;
const int F = 2;
const int N = 2005;
double ans;
double g[N];
double dp[N][N][F];
int m, n, v, e, x, y, z;
int c[N], d[N];
int a[C][C];
int main() {
    scanf("%d %d %d %d", &n, &m, &v, &e);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &c[i]);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &d[i]);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%lf", &g[i]);
    }
    for (int i = 1; i <= v; ++i) {
        for (int j = 1; j <= v; ++j) {
            a[i][j] = 0x3f3f3f3f;
        }
    }
    for (int i = 1; i <= e; ++i) {
        scanf("%d %d %d", &x, &y, &z);
        a[x][y] = a[y][x] = std::min(a[x][y], z);
    }
    for (int i = 1; i <= v; ++i) {
        a[i][i] = 0;
    }
    for (int k = 1; k <= v; ++k) {
        for (int i = 1; i <= v; ++i) {
            for (int j = 1; j <= v; ++j) {
                a[i][j] = std::min(a[i][j], a[i][k] + a[k][j]);
            }
        }
    }
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            dp[i][j][0] = 1e9;
            dp[i][j][1] = 1e9;
        }
    }
    dp[0][0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        dp[i][0][0] = dp[i - 1][0][0] + a[c[i - 1]][c[i]];
        for (int j = 1; j <= m; ++j) {
            dp[i][j][0] = std::min(dp[i - 1][j][0] + a[c[i]][c[i - 1]], dp[i - 1][j][1] + a[d[i - 1]][c[i]] * g[i - 1] + a[c[i - 1]][c[i]] * (1 - g[i - 1]));
            dp[i][j][1] = dp[i - 1][j - 1][1];
            dp[i][j][1] += a[d[i - 1]][d[i]] * g[i - 1] * g[i];
            dp[i][j][1] += a[d[i - 1]][c[i]] * g[i - 1] * (1 - g[i]);
            dp[i][j][1] += a[c[i - 1]][d[i]] * (1 - g[i - 1]) * g[i];
            dp[i][j][1] += a[c[i - 1]][c[i]] * (1 - g[i - 1]) * (1 - g[i]);
            dp[i][j][1] = std::min(dp[i][j][1], dp[i - 1][j - 1][0] + a[c[i - 1]][d[i]] * g[i] + a[c[i - 1]][c[i]] * (1 - g[i]));
        }
    }
    ans = 1e10;
    for (int i = 0; i <= m; ++i) {
        ans = std::min(ans, dp[n][i][0]);
        ans = std::min(ans, dp[n][i][1]);
    }
    printf("%.2f\n", ans);
    return 0;
}