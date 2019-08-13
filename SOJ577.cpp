#include <bits/stdc++.h>
const int mod = 998244353;
const int N_MAX = 105;
namespace Subtask1 {
    const int N = 52;
    const int M = 102;
    int ans;
    int dp[N][N][N][M];
    int main();
}
int n, m, k, max;
int a[N_MAX];
int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        max = std::max(max, a[i]);
    }
    if (max <= 100) {
        Subtask1::main();
    }
    return 0;
}
namespace Subtask1 {
    inline int main() {
        dp[0][0][0][0] = 1;
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                for (int l = 0; l <= k; ++l) {
                    for (int w = a[i]; w; --w) {
                        if (!dp[i][j][l][w]) {
                            continue;
                        }
                        // printf("D: dp[%d][%d][%d][%d] = %d;\n", i, j, l, w, dp[i][j][l][w]);
                        (dp[i + 1][j][l][a[i + 1]] += dp[i][j][l][w]) %= mod;
                        if (w + l <= k) {
                            (dp[i][j + 1][w + l][0] += dp[i][j][l][w]) %= mod;
                        }
                        for (int v = 1; v < w; ++v) {
                            if (l + a[i] % v <= k) {
                                (dp[i][j + 1][l + a[i] % v][v] += dp[i][j][l][w]) %= mod;
                            }
                        }
                    }
                    // printf("D: dp[%d][%d][%d][%d] = %d;\n", i, j, l, 0, dp[i][j][l][0]);
                    (dp[i + 1][j][l][a[i + 1]] += dp[i][j][l][0]) %= mod;
                }
            }
        }
        for (int i = 0; i <= a[n]; ++i) {
            (ans += dp[n][m][k][i]) %= mod;
        }
        printf("%d\n", ans);
        return 0;
    }
}