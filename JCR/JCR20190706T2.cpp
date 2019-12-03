#include <bits/stdc++.h>
const int N = 105;
int min, n, q, x, y;
int p[N];
int f[N][N];
int main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    scanf("%d", &n);
    memset(f, 127, sizeof(f));
    for (int i = 1; i < n; ++i) {
        scanf("%d %d", &x, &y);
        f[x][y] = 1;
        f[y][x] = 1;
        f[i][i] = 0;
    }
    f[n][n] = 0;
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                f[i][j] = std::min(f[i][j], f[i][k] + f[k][j]);
            }
        }
    }
    scanf("%d", &q);
    while (q--) {
        scanf("%d", &x);
        for (int i = 1; i <= x; ++i) {
            scanf("%d", &p[i]);
        }
        min = 1e9;
        for (int i = 1; i <= n; ++i) {
            y = 0;
            for (int j = 1; j <= x; ++j) {
                y = std::max(y, f[i][p[j]]);
            }
            min = std::min(min, y);
        }
        printf("%d\n", min);
    }
    return 0;
}