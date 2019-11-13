#include <bits/stdc++.h>
const int A = 20;
const int B = 10;
const int C = 2;
char a[A], b[A], c[A];
int n;
long long as, bs, ans;
/*
 * dp[i][j][k] ->
 * i: number to select
 * j: number now
 * k: limit
 */
long long dp[A][B][C];
long long check(char *, int);
int main() {
    std::ios::sync_with_stdio(0);
    memset(c, 9, sizeof(c));
    while (std::cin >> as >> bs) {
        memset(dp, 0, sizeof(dp));
        sprintf(a, "%lld", as - 1);
        sprintf(b, "%lld", bs);
        ans = 0;
        n = strlen(b);
        for (int i = 0; i < n; ++i) {
            b[i] -= '0';
        }
        ans += check(b, n);
        for (int i = 1; i < n; ++i) {
            ans += check(c, n - i);
        }
        n = strlen(a);
        for (int i = 0; i < n; ++i) {
            a[i] -= '0';
        }
        ans -= check(a, n);
        for (int i = 1; i < n; ++i) {
            ans -= check(c, n - i);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
inline long long check(char *a, int n) {
    long long ans = 0;
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i < a[0]; ++i) {
        dp[0][i][0] = 1;
    }
    if (a[0]) {
        dp[0][a[0]][1] = 1;
    }
    for (int i = 0; i < n - 1; ++i) {
        for (int j = a[i]; j < a[i + 1]; ++j) {
            dp[i + 1][j][0] += dp[i][a[i]][1];
        }
        if (a[i] <= a[i + 1]) {
            dp[i + 1][a[i + 1]][1] += dp[i][a[i]][1];
        }
        for (int j = 0; j < 10; ++j) {
            for (int k = j; k < 10; ++k) {
                dp[i + 1][k][0] += dp[i][j][0];
            }
        }
    }
    for (int i = 0; i < 10; ++i) {
        ans += dp[n - 1][i][0] + dp[n - 1][i][1];
    }
    return ans;
}