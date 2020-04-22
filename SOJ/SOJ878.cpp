#include <bits/stdc++.h>
const int N = 11;
const int mod = 998244353;
int a[N][N][N];
long long val[N][N][N];
inline long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    long long tmp = exgcd(b, a % b, x, y);
    std::swap(x, y);
    y = y - x * (a / b);
    return tmp;
}
inline long long inv(long long a) {
    long long x, y;
    exgcd(a, mod, x, y);
    return (x % mod + mod) % mod;
}
inline long long have(const int xl, const int yl, const int zl, const int xr,
                      const int yr, const int zr) {
    return a[xr][yr][zr] - a[xl][yr][zr] - a[xr][yl][zr] - a[xr][yr][zl] +
           a[xl][yl][zr] + a[xl][yr][zl] + a[xr][yl][zl] - a[xl][yl][zl];
}
inline long long valu(const int xl, const int yl, const int zl, const int xr,
                      const int yr, const int zr) {
    return (val[xr][yr][zr] - val[xl][yr][zr] - val[xr][yl][zr] -
            val[xr][yr][zl] + val[xl][yl][zr] + val[xl][yr][zl] +
            val[xr][yl][zl] - val[xl][yl][zl]) %
           mod;
}
int main() {
    register int n, m, k, w, xl, yl, zl, xr, yr, zr;
    register long long ans = 0;
    std::cin >> n >> m >> k >> w;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            for (int l = 1; l <= k; ++l) {
                std::cin >> a[i][j][l];
                a[i][j][l] ^= 1;
                a[i][j][l] += a[i - 1][j][l];
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            for (int l = 1; l <= k; ++l) {
                std::cin >> val[i][j][l];
                val[i][j][l] += val[i - 1][j][l];
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            for (int l = 1; l <= k; ++l) {
                a[i][j][l] += a[i][j - 1][l];
                val[i][j][l] += val[i][j - 1][l];
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            for (int l = 1; l <= k; ++l) {
                a[i][j][l] += a[i][j][l - 1];
                val[i][j][l] += val[i][j][l - 1];
            }
        }
    }
    for (xl = 0; xl < n; ++xl) {
        for (yl = 0; yl < m; ++yl) {
            for (zl = 0; zl < k; ++zl) {
                for (xr = xl + 1; xr <= n; ++xr) {
                    for (yr = yl + 1; yr <= m; ++yr) {
                        for (zr = zl + 1; zr <= k; ++zr) {
                            if (!have(xl, yl, zl, xr, yr, zr)) {
                                ans += valu(xl, yl, zl, xr, yr, zr);
                            }
                        }
                    }
                }
                ans %= mod;
            }
        }
    }
    std::cout << ans * inv(n * m * k * (n + 1ll) * (m + 1) * (k + 1) / 8) % mod
              << std::endl;
    return 0;
}