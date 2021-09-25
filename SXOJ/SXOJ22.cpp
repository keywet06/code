#include <bits/stdc++.h>

#define Deb std::cerr
#define Delin Deb << "[Debug] at Line " << __LINE__
#define Debug Delin << " : "
#define Deline Delin << std::endl

using int64 = long long;

const int N = 105;
const int P = 998244353;

int n, x, y;

int64 p, q, u, v;
int64 pre[N], re[N], inv[N], ans[N];
int64 f[N][N], g[N][N];

inline int64 power(int64 x, int64 y) {
    int64 ret = 1;
    while (y) ret = y & 1 ? ret * x % P : ret, x = x * x % P, y >>= 1;
    return ret;
}

inline int64 C(int m, int n) { return pre[m] * re[n] % P * re[m - n] % P; }

inline int64 Inv(int64 x) { return power(x, P - 2); }

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    pre[0] = inv[0] = inv[1] = re[0] = 1;
    for (int i = 1; i < N; ++i) pre[i] = pre[i - 1] * i % P;
    for (int i = 2; i < N; ++i) inv[i] = (P - P / i) * inv[P % i] % P;
    for (int i = 1; i < N; ++i) re[i] = re[i - 1] * inv[i] % P;
    std::cin >> n >> x >> y, p = x * power(y, P - 2) % P, q = P + 1 - p;
    f[1][1] = g[1][1] = 1;
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j <= i; ++j) {
            f[i][j] %= P, g[i][j] %= P;
            for (int k = 1; k <= i + 1; ++k) {
                f[i + 1][k] += f[i][j] * (k > j ? q : p) % P;
                g[i + 1][k] += g[i][j] * (k > j ? p : q) % P;
            }
        }
    }
    for (int j = 1; j <= n; ++j) f[n][j] %= P, g[n][j] %= P;
    for (int i = 1; x = n - i + 1; ++i) {
        u = v = 0;
        for (int j = 1; j <= i; ++j) {
            for (int k = 1; k <= x; ++k) {
                u += f[i][j] * g[x][k] % P * C(j + k - 2, j - 1) % P *
                     C(i - j + x - k, i - j) % P;
                v += (j + k - 1) * f[i][j] % P * g[x][k] % P *
                     C(j + k - 2, j - 1) % P * C(i - j + x - k, i - j) % P;
            }
        }
        u %= P, v %= P;
        ans[i] = v * Inv(u) % P;
        std::cout << ans[i] << " \n"[i == n];
    }
    return 0;
}