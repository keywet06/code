#include <bits/stdc++.h>

using int64 = long long;

const int N = 505;
const int K = 4;
const int Y = 1 << K;
const int Z = 1 << Y;
const int P = 998244353;

int Cy, Cz, Cw, n, k, c, o;
int is[Y], g[Y], p[Y];

int64 ans;
int64 f[N][Y];

bool pd(int x) { return is[x] && ~p[x & Cw]; }

int main() {
    std::cin >> n >> k, Cy = 1 << k, Cz = 1 << Cy, Cw = (1 << (k - 1)) - 1;
    if (k == 1) {
        ans = 1;
        for (int i = 2; i < n; ++i) ans = ans * 2 % P;
        std::cout << ans << std::endl;
        return 0;
    }
    for (int i = 0; i < Cz; ++i) {
        c = 0;
        memset(is, 0, sizeof(is));
        memset(p, 255, sizeof(p));
        for (int j = 0; j < Cy; ++j) {
            if (i & (1 << (Cy - j - 1))) is[j] = 1;
        }
        for (int j = 0; j <= Cy - k; ++j) {
            if (!is[(i >> j) & (Cy - 1)]) {
                c = 1;
                break;
            }
        }
        if (c) continue;
        if (n == 1 << k) {
            ++ans;
            continue;
        }
        for (int j = 0; j < 1 << (k - 1); ++j) {
            if ((is[j] || is[j | (1 << (k - 1))]) &&
                (is[j << 1] || is[j << 1 | 1])) {
                p[j] = c, g[c++] = j;
            }
        }
        f[1 << k][p[i & Cw]] = 1;
        for (int j = 1 << k; j < n; ++j) {
            for (int l = 0; l < c; ++l) {
                f[j][l] %= P;
                if (pd(o = g[l] << 1)) f[j + 1][p[o & Cw]] += f[j][l];
                if (pd(o = g[l] << 1 | 1)) f[j + 1][p[o & Cw]] += f[j][l];
            }
        }
        for (int j = 0; j < c; ++j) {
            f[n - 1][j] %= P;
            if (is[g[j] << 1]) ans += f[n - 1][j];
            if (is[g[j] << 1 | 1]) ans += f[n - 1][j];
        }
        for (int j = 0; j <= n + 1; ++j) {
            for (int l = 0; l < c; ++l) f[j][l] = 0;
        }
        ans %= P;
    }
    std::cout << ans << std::endl;
    return 0;
}