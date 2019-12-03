#include <bits/stdc++.h>
const int N = 105;
int r, s, p, sum;
double ans, tmp;
double dp[N][N][N];
int main() {
    scanf("%d %d %d", &r, &s, &p);
    dp[r][s][p] = 1;
    for (int i = r; ~i; --i) {
        for (int j = s; ~j; --j) {
            for (int k = p; ~k; --k) {
                tmp = i * j + j * k + k * i;
                if (i && j) {
                    dp[i][j - 1][k] += dp[i][j][k] * (i * j / tmp);
                }
                if (j && k) {
                    dp[i][j][k - 1] += dp[i][j][k] * (j * k / tmp);
                }
                if (k && i) {
                    dp[i - 1][j][k] += dp[i][j][k] * (k * i / tmp);
                }
            }
        }
    }
    ans = 0;
    for (int i = 1; i <= r; ++i) {
        ans += dp[i][0][0];
    }
    printf("%.8f ", ans);
    ans = 0;
    for (int i = 1; i <= s; ++i) {
        ans += dp[0][i][0];
    }
    printf("%.8f ", ans);
    ans = 0;
    for (int i = 1; i <= p; ++i) {
        ans += dp[0][0][i];
    }
    printf("%.8f\n", ans);
    return 0;
}