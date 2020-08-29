#include <bits/stdc++.h>
using int64 = long long;
const int N = 300005;
const int M = 998244353;
int64 n, m;
int64 f[N], inv[N], fac[N], g[N];
int64 ksm(int64 x, int64 y) {
    int64 ans = 1;
    for (; y; y >>= 1, x = x * x % M) {
        if (y & 1) (ans *= x) %= M;
    }
    return ans;
}
void init(int64 y[], int64 len) {
    for (int64 i = 1, j = len / 2; i < len - 1; ++i) {
        if (i < j) std::swap(y[i], y[j]);
        int64 k = len / 2;
        while (j >= k) {
            j -= k;
            k /= 2;
        }
        j += k;
    }
}
void ntt(int64 y[], int64 len, int64 opt) {
    init(y, len);
    for (int64 h = 2; h <= len; h <<= 1) {
        int64 wn = ksm(3, (M - 1) / h);
        if (opt == -1) wn = ksm(wn, M - 2);
        for (int64 j = 0; j < len; j += h) {
            int64 w = 1;
            for (int64 k = j; k < j + h / 2; ++k) {
                int64 u = y[k], v = y[k + h / 2] * w % M;
                y[k] = (u + v) % M;
                y[k + h / 2] = (M + u - v) % M;
                w = w * wn % M;
            }
        }
    }
    if (opt == 1) return;
    int64 temp = ksm(len, M - 2);
    for (int64 i = 0; i < len; ++i) (y[i] *= temp) %= M;
}
void calc(int64 y[], int64 n) {
    static int64 a[N], b[N];
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    for (int64 i = 0; i <= n; ++i)
        a[i] = ksm(i + 1, n) * inv[i] % M, b[i] = i & 1 ? M - inv[i] : inv[i];
    int64 len = 1;
    while (len <= 2 * n + 5) len <<= 1;
    ntt(a, len, 1);
    ntt(b, len, 1);
    for (int64 i = 0; i < len; ++i) (a[i] *= b[i]) %= M;
    ntt(a, len, -1);
    for (int64 i = 0; i < len; ++i) y[i] = a[i] * fac[i] % M;
}
int main() {
    std::cin >> n >> m;
    if (n > m) std::swap(n, m);
    fac[0] = inv[0] = 1;
    for (int64 i = 1; i < N; ++i) {
        fac[i] = fac[i - 1] * i % M;
        inv[i] = ksm(fac[i], M - 2);
    }
    calc(f, n);
    calc(g, m);
    int64 ans = 0;
    for (int64 i = 0; i <= n; ++i) (ans += f[i] * g[i]) %= M;
    std::cout << ans << std::endl;
    return 0;
}