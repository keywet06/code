#include <bits/stdc++.h>
const int N = 3000005;
const double pi = acos(-1);
typedef std::complex<double> comp;
int n, m, x, l;
int rev[N];
comp a[N], b[N], t[N];
inline void change(comp *f, int n) {
    for (int i = 0; i < n; ++i) {
        rev[i] = rev[i >> 1] >> 1 | (i & 1 ? n : 0) >> 1;
    }
    for (int i = 0; i < n; ++i) if (i < rev[i]) std::swap(f[i], f[rev[i]]);
}
inline void fft(comp *f, int n, int rev) {
    change(f, n);
    register comp step, cur, g, h;
    for (int l = 2; l <= n; l <<= 1) {
        step = comp(cos(2 * pi / l), sin(2 * pi * rev / l));
        for (int b = 0; b < n; b += l) {
            cur = comp(1, 0);
            for (int k = b; k < b + (l >> 1); ++k) {
                g = f[k], h = f[k + (l >> 1)] * cur;
                f[k] = g + h;
                f[k + (l >> 1)] = g - h;
                cur *= step;
            }
        }
    }
    if (!~rev) for (int i = 0; i < n; ++i) f[i] /= n;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m;
    ++n, ++m;
    for (int i = 0; i < n; ++i) std::cin >> x, a[i].real(x);
    for (int i = 0; i < m; ++i) std::cin >> x, b[i].real(x);
    l = 1;
    while (l < n + m) l <<= 1;
    fft(a, l, 1), fft(b, l, 1);
    for (int i = 0; i < l; ++i) a[i] *= b[i];
    fft(a, l, -1);
    for (int i = 0; i < n + m - 1; ++i) {
        a[i] = a[i] + 0.5;
        std::cout << int(a[i].real()) << ' ';
    }
    std::cout << std::endl;
    return 0;
}