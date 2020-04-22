#include <bits/stdc++.h>
const int N = 104;
const int mod[] = {998244353, 1000000007, 1000000009};
int n, m, a[N][N], cnt;
char s[N];
long long ans, f[3][N][N], g[3][N][N];
int add(int a, int b, int p) {
    a += b;
    if (a >= p) return a - p;
    return a;
}
int check(int x, int y) {
    if (a[1][1] == 1 || a[n][m] == 1 || (x == 1 && y == 1) ||
        (x == n && y == m))
        return cnt - 1;
    int ans = 0;
    a[x][y] = 1;
    f[0][1][1] = f[1][1][1] = f[2][1][1] = 1;
    g[0][n][m] = g[1][n][m] = g[2][n][m] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            if (i == 1 && j == 1) {
                continue;
            }
            if (a[i][j]) {
                for (int k = 0; k <= 2; ++k) {
                    f[k][i][j] = 0;
                }
            } else {
                for (int k = 0; k <= 2; ++k) {
                    f[k][i][j] = add(f[k][i][j - 1], f[k][i - 1][j], mod[k]);
                }
            }
        }
    for (int i = n; i >= 1; --i)
        for (int j = m; j >= 1; --j) {
            if (i == n && j == m) {
                continue;
            }
            if (a[i][j]) {
                for (int k = 0; k <= 2; ++k) {
                    g[k][i][j] = 0;
                }
            } else {
                for (int k = 0; k <= 2; ++k) {
                    g[k][i][j] = add(g[k][i][j + 1], g[k][i + 1][j], mod[k]);
                }
            }
        }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i][j]) continue;
            int cnt = 0;
            for (int k = 0; k <= 2; ++k)
                if (f[k][i][j] * g[k][i][j] % mod[k] == f[k][n][m]) {
                    cnt++;
                } else {
                    break;
                }
            if (cnt == 3) ans++;
        }
    }
    a[x][y] = 0;
    return ans;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s + 1);
        for (int j = 1; j <= m; ++j)
            if (s[j] == '.') {
                a[i][j] = 0, cnt++;
            } else {
                a[i][j] = 1;
            }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i][j] == 1) {
                continue;
            }
            ans += check(i, j);
        }
    }
    printf("%lld", ans / 2);
    return 0;
}