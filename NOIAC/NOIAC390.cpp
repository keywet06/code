#include <bits/stdc++.h>
const int M = 5005;
const int N = 105;
const int T = 35;
int n, now, t;
int dp[M];
int a[N][T];
int main() {
    scanf("%d %d %d", &n, &now, &t);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= t; ++j) {
            scanf("%d", &a[i][j]);
        }
    }
    for (int i = 1; i < t; ++i) {
        memset(dp, 0, sizeof(dp));
        for (int j = 1; j <= n; ++j) {
            if (a[j][i + 1] - a[j][i] <= 0) {
                continue;
            }
            for (int k = a[j][i]; k <= now; ++k) {
                dp[k] = std::max(dp[k], dp[k - a[j][i]] + a[j][i + 1] - a[j][i]);
            }
        }
        now += dp[now];
    }
    printf("%d\n", now);
    return 0;
}