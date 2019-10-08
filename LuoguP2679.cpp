#include <bits/stdc++.h>
const int M = 1005;
const int N = 205;
char a[M];
char b[N];
long long n, m, l;
long long dp[N][N] = {1}, gd[N][N];
int main() {
    scanf("%lld %lld %lld %s %s", &n, &m, &l, a, b);
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= 1; j--) {
            for (int k = l; k >= 1; k--) {
                dp[j][k] = (dp[j][k] + (gd[j][k] = a[i - 1] == b[j - 1] ? gd[j - 1][k] + dp[j - 1][k - 1] : 0)) % 1000000007;
            }
        }
    }
    printf("%lld\n", dp[m][l]);
}