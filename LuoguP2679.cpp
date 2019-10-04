#include <bits/stdc++.h>
const int mod = 1000000007;
const int C = 2;
const int K = 205;
const int M = 205;
const int N = 1005;
char s1[N], s2[N];
int n, m, k;
long long dp[N][M][K][C];
template<typename Type> Type &tomax(Type&, Type);
int main() {
    scanf("%d %d %d", &n, &m, &k);
    if (std::max(n, m) < k) {
        printf("0\n");
        return 0;
    }
    scanf("%s", s1 + 1);
    scanf("%s", s2 + 1);
    dp[1][1][0][1] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            for (int l = 1; l <= k; ++l) {
                (dp[i][j][l][1] += dp[i][j - 1][l][1] + dp[i - 1][j][l][1]) %= mod;
                if (s1[i] == s2[j]) {
                    (dp[i][j][l][0] += dp[i - 1][j - 1][l - 1][1] + dp[i - 1][j - 1][l][0]) %= mod;
                    (dp[i][j][l][1] += dp[i][j][l][0]) %= mod;
                }
            }
        }
    }
    printf("%d\n", dp[n][m][k][1]);
    return 0;
}
template<typename Type> inline Type &tomax(Type &x, Type y) {
    return x = std::max(x, y);
}