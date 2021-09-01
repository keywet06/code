#include <bits/stdc++.h>

using int64 = long long;

const int P = 1000000007;
const int K = 15;
const int N = 500005;

int n, k, e, flag;
int w[K], dn[K], up[K], o[K], l[K], q[K], t[K];
int c[N], d[N];

int64 x, y, z, ans;
int64 f[K], g[K], bi[K];

inline int64 power(int64 x, int64 y) {
    return y ? (y & 1 ? power(x * x % P, y >> 1) * x % P
                      : power(x * x % P, y >> 1))
             : 1;
}

inline int64 inv(int64 x) { return power(x, P - 2); }

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> k;
    for (int i = 1; i <= k; ++i) std::cin >> w[i], e = std::max(e, w[i]);
    for (int i = 1; i <= n; ++i) std::cin >> c[i] >> d[i];
    for (int i = 1; i <= n; ++i) {
        o[c[i]] += d[i], e = o[c[i]] > up[c[i]] || o[c[i]] < dn[c[i]];
        up[c[i]] = std::max(up[c[i]], o[c[i]]);
        dn[c[i]] = std::min(dn[c[i]], o[c[i]]);
        if (up[c[i]] - dn[c[i]] > w[c[i]] && (flag = 1)) break;
        x = 1;
        for (int j = 1; j <= k; ++j) {
            x = x * (w[j] - up[j] + dn[j] + (j == c[i] && e)) % P;
        }
        ans += x;
    }
    if (flag) return std::cout << ans % P << std::endl, 0;
    for (int i = 1; i <= k; ++i) w[i] -= t[i] = up[i] - dn[i], q[i] = o[i];
    for (int i = 1; i <= n; ++i) {
        o[c[i]] += d[i], e = 0;
        if (o[c[i]] > up[c[i]]) ++l[c[i]], up[c[i]] = o[c[i]], e = 1;
        if (o[c[i]] < dn[c[i]]) ++l[c[i]], dn[c[i]] = o[c[i]], e = 1;
        memset(g, 0, sizeof(g)), g[0] = 1;
        for (int j = 1; j <= k; ++j) {
            x = -std::abs(q[j]), y = w[j] - l[j] - x + (j == c[i] && e);
            for (int l = j; l; --l) g[l] = (x * g[l - 1] + y * g[l]) % P;
            g[0] = g[0] * y % P;
        }
        for (int j = 0; j <= k; ++j) f[j] = (f[j] + g[j]) % P;
    }
    for (int i = 1; i <= k + 2; ++i) {
        x = 1;
        for (int j = 0; j <= k; ++j) bi[i] += x * f[j] % P, x = x * i % P;
        bi[i] = (bi[i] % P + P) % P;
    }
    for (int i = 2; i <= k + 2; ++i) bi[i] = (bi[i - 1] + bi[i]) % P;
    memset(f, 0, sizeof(f));
    for (int i = 1; i <= k + 2; ++i) {
        memset(g, 0, sizeof(g)), g[0] = 1, z = 1;
        for (int j = 1; j <= k + 2; ++j) {
            if (i == j) continue;
            x = 1, y = -j;
            for (int l = j; l; --l) g[l] = (x * g[l - 1] + y * g[l]) % P;
            g[0] = g[0] * y % P, z = z * (i - j) % P;
        }
        z = bi[i] * inv(z) % P;
        for (int j = 0; j <= k + 2; ++j) f[j] = (f[j] + g[j] * z) % P;
    }
    x = 1e15;
    for (int i = 1; i <= k; ++i) {
        if (l[i]) x = std::min(x, int64(w[i] - 1) / l[i]);
    }
    if (x == 1e15) return std::cout << -1 << std::endl, 0;
    y = 1;
    for (int i = 0; i <= k + 2; ++i) ans += f[i] * y % P, y = y * x % P;
    for (int i = 1; i <= k; ++i) {
        (q[i] > 0 ? up : dn)[i] += q[i] * (x - 1);
        o[i] += q[i] * (x - 1);
    }
    for (int i = 1; i <= k; ++i) w[i] += t[i];
    while (1) {
        for (int i = 1; i <= n; ++i) {
            o[c[i]] += d[i], e = o[c[i]] > up[c[i]] || o[c[i]] < dn[c[i]];
            up[c[i]] = std::max(up[c[i]], o[c[i]]);
            dn[c[i]] = std::min(dn[c[i]], o[c[i]]);
            if (up[c[i]] - dn[c[i]] > w[c[i]] && (flag = 1)) {
                std::cout << (ans % P + P) % P << std::endl;
                return 0;
            }
            x = 1;
            for (int j = 1; j <= k; ++j) {
                x = x * (w[j] - up[j] + dn[j] + (j == c[i] && e)) % P;
            }
            ans += x;
        }
    }
    return 0;
}