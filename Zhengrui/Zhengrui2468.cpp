#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

#ifndef OCT_MIAD_HPP
#define OCT_MIAD_HPP

#define templ template <typename Type1, typename Type2>
templ inline Type1 Min(Type1 x, Type2 y) { return x < y ? x : y; }
templ inline Type1 Max(Type1 x, Type2 y) { return y < x ? x : y; }
templ inline Type1 &Mid(Type1 &x, Type2 y) { return x < y ? x : x = y; }
templ inline Type1 &Mad(Type1 &x, Type2 y) { return y < x ? x : x = y; }
#undef templ

#define templ template <typename Type1, typename Type2, typename... Args>
templ inline Type1 Min(Type1 x, Type2 y, Args... args) { return Min(Min(x, y), args...); }
templ inline Type1 Max(Type1 x, Type2 y, Args... args) { return Max(Max(x, y), args...); }
templ inline Type1 &Mid(Type1 &x, Type2 y, Args... args) { return Mid(Mid(x, y), args...); }
templ inline Type1 &Mad(Type1 &x, Type2 y, Args... args) { return Mad(Mad(x, y), args...); }
#undef templ

#endif

#define KB \
    if (!k) break

using int64 = long long;

const int C = 20;
const int N = 66000;

int n, m;
int a[C], b[C];
int f[N], h[N][C], g[N][C];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n;
    m = (1 << n) - 1;
    for (int i = 0; i < n; ++i) std::cin >> a[i] >> b[i];
    memset(f, 60, sizeof(f));
    memset(h, 60, sizeof(h));
    memset(g, 60, sizeof(g));
    g[0][0] = f[0] = 0;
    for (int j = 0; j < n; ++j) h[0][j] = -f[1];
    for (int i = 0; i < n; ++i) f[1 << i] = 0;
    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j < n; ++j) {
            if ((1 << j) & i) f[i] = std::min(f[i], a[j] + h[i ^ (1 << j)][j]);
        }
        if (i == m) break;
        for (int j = 1; j < n; ++j) {
            for (int k = i; k; k = i & (k - 1)) {
                Mid(g[i][j], Max(g[i ^ k][j - 1], f[k])); KB; k = i & (k - 1);
                Mid(g[i][j], Max(g[i ^ k][j - 1], f[k]));
            }
            if (++j >= n) break;
            for (int k = i; k; k = i & (k - 1)) {
                Mid(g[i][j], Max(g[i ^ k][j - 1], f[k])); KB; k = i & (k - 1);
                Mid(g[i][j], Max(g[i ^ k][j - 1], f[k]));
            }
        }
        for (int j = 0; j < n; ++j) {
            for (int k = i; k; k = i & (k - 1)) {
                Mid(h[i][j], Max(g[k][b[j]], a[j] + h[i ^ k][j])), k = i & (k - 1); KB;
                Mid(h[i][j], Max(g[k][b[j]], a[j] + h[i ^ k][j])), k = i & (k - 1);
            }
            if (++j >= n) break;
            for (int k = i; k; k = i & (k - 1)) {
                Mid(h[i][j], Max(g[k][b[j]], a[j] + h[i ^ k][j])), k = i & (k - 1); KB;
                Mid(h[i][j], Max(g[k][b[j]], a[j] + h[i ^ k][j])), k = i & (k - 1);
            }
        }
    }
    std::cout << f[m] << '\n';
    return 0;
}