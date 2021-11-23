#include <bits/stdc++.h>

template<typename _Tp>
inline _Tp &mid(_Tp &x, _Tp y) { return x < y ? x : (x = y); }

using int64 = long long;

const int N = 10005;
const int M = 500005;
const int64 INF = 500000000005;

int n, c, m, s, l;
int a[N], d[N];

int64 ans;
int64 _f[M], _g[M], *f = _f, *g = _g;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    for (int i = 1; i < n; ++i) d[i] = a[i + 1] - a[i];
    std::sort(d + 1, d + n), c = 1;
    while (c <= n && !d[c]) ++c;
    m = 0, f[0] = 0;
    for (; c < n; ++c) {
        l = m, m += c * d[c], s += d[c];
        for (int i = 0; i <= m; ++i) g[i] = INF;
        for (int i = 0; i <= l; ++i) {
            mid(g[i + s], f[i] + s * s);
            mid(g[i + d[c] * c], f[i] + 2 * d[c] * i + d[c] * d[c] * int64(c));
        }
        std::swap(f, g);
    }
    ans = INF * n;
    for (int64 i = 0; i <= m; ++i) mid(ans, f[i] * n - i * i);
    std::cout << ans << std::endl;
    return 0;
}