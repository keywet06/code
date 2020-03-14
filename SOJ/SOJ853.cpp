#include <bits/stdc++.h>
const int N = 1005;
int n, m, x, y, k, f, t;
int a[2][N][N], v[2][N][N];
int main() {
    std::cin >> n >> m >> k;
    for (int i = 1; i <= k; ++i) {
        std::cin >> x >> y;
        std::cin >> a[0][x][y];
        a[1][x][y] = a[0][x][y];
        v[0][x][y] = 2;
    }
    for (int i = 0; i <= m + 1; ++i) {
        v[0][0][i] = v[0][n + 1][i] = v[1][0][i] = v[1][n + 1][i] = 2;
    }
    for (int i = 1; i <= n; ++i) {
        v[0][i][0] = v[0][i][m + 1] = v[1][i][0] = v[1][i][m + 1] = 2;
    }
    f = 1;
    while (f) {
        f = 0;
        for (int c = 0; c < 2; ++c) {
            for (x = 1; x <= n; ++x) {
                for (y = 1; y <= m; ++y) {
                    if (v[c][x][y] == 2) {
                        continue;
                    }
                    t = a[c][x][y];
                    if (!v[c][x][y]){
                        t = c ? INT_MIN : INT_MAX;
                        ++f;
                    }
                    if (v[!c][x + 1][y]) {
                        t = c ? std::max(t, a[!c][x + 1][y]) : std::min(t, a[!c][x + 1][y]);
                        v[c][x][y] = 1;
                    }
                    if (v[!c][x - 1][y]) {
                        t = c ? std::max(t, a[!c][x - 1][y]) : std::min(t, a[!c][x - 1][y]);
                        v[c][x][y] = 1;
                    }
                    if (v[!c][x][y + 1]) {
                        t = c ? std::max(t, a[!c][x + 1][y]) : std::min(t, a[!c][x + 1][y]);
                        v[c][x][y] = 1;
                    }
                    if (v[!c][x][y - 1]) {
                        t = c ? std::max(t, a[!c][x - 1][y]) : std::min(t, a[!c][x - 1][y]);
                        v[c][x][y] = 1;
                    }
                    if (!v[c][x][y]){
                        a[c][x][y] = 0;
                        --f;
                    } else
                    if (t != a[c][x][y]) {
                        a[c][x][y] = t;
                    } else {
                        --f;
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            ans = (ans + a[0][i][j]) % 998244353;
        }
    }
    std::cout << (ans + 998244353) % 998244353;
    return 0;
}
