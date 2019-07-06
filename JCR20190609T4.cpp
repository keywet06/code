#include <bits/stdc++.h>
const int N = 200;
int ans, m, n, x, y;
int a[N][N];
int main() {
    freopen("contest.in", "r", stdin);
    freopen("contest.out", "w", stdout);
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d", &x, &y);
        a[x][y] = 1;
        a[y][x] = -1;
    }
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (a[i][k] == 1 && a[k][j] == 1) {
                    a[i][j] = 1;
                }
                if (a[i][k] == -1 && a[k][j] == -1) {
                    a[i][j] = -1;
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        x = 1;
        for (int j = 1; j <= n; ++j) {
            x &= a[i][j] || i == j;
        }
        ans += x;
    }
    printf("%d\n", ans);
    return 0;
}