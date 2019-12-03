#include <bits/stdc++.h>
const int N = 2005;
long long n;
long long a[N];
long long dp[N][N][2];
int main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
    }
    for (int i = 1; i <= (n + 1) / 2; ++i) {
        dp[i][1][0] = LONG_LONG_MIN;
        dp[i][1][1] = a[i];
        for (int j = 2; j <= n; ++j) {
            dp[i][j][0] = dp[i][j - 1][1];
            dp[i][j][1] = dp[i - 1][j - 1][0] + a[j];
        }
        printf("%lld\n", std::max(dp[i][n][1], dp[i][n][0]));
    }
    return 0;
}