#include <bits/stdc++.h>
const int C = 2;
const int M = 12;
const int M1 = 1025;
const int N = 105;
char read[M];
int m, n, t, can, ans, c, d, x, w;
int map[N];
int st[M];
int logs[M1];
int dp[C][M1][M1];
int main() {
    // std::ios::sync_with_stdio(0);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        std::cin >> read;
        for (int j = 0; j < m; ++j) {
            map[i] |= (read[j] == 'P') << j;
        }
    }
    for (int i = 0; i <= m; ++i) {
        logs[1 << i] = 1;
    }
    dp[t = 0][(1 << m) - 1][(1 << m) - 1] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 1 << m; ++j) {
            for (int k = 0; k < 1 << k; ++k) {
                if (!dp[t][j][k]) {
                    continue;
                }
                can = map[i] & j & k;
                c = 0;
                while (can) {
                    st[++c] = logs[can & (-can)];
                    can &= can - 1;
                }
                for (int l = 0; l < 1 << c; ++l) {
                    d = 0;
                    x = -3;
                    w = 1;
                    can = map[i] & j & k;
                    for (int o = 0; o < c; ++o) {
                        if ((1 << o) & l) {
                            if (st[o] - x < 3) {
                                w = 0;
                                break;
                            }
                            x = st[o];
                            can ^= 1 << st[o];
                            ++d;
                        }
                    }
                    if (!w) {
                        continue;
                    }
                    ans = std::max(ans, dp[t ^ 1][k][can] =
                        std::max(dp[t ^ 1][k][can], dp[t][j][k] + d));
                }
            }
        }
        t ^= 1;
    }
    printf("%d\n", ans - 1);
    return 0;
}