#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
const int N = 40000005;
const long long V = (1 << 30) - 1;
int n, type;
unsigned int ch, x;
unsigned int q[N], f[N];
long long a[N];
inline void gch() { ch = getchar(); }
inline unsigned int read() {
    gch();
    while (ch < '0' || ch > '9') gch();
    x = ch ^ 48, gch();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + (ch ^ 48), gch();
    return x;
}
template <typename _Tp>
inline void read(_Tp &x) {
    x = read();
}
inline long long len(int x) { return a[x] - a[f[x]]; }
inline __int128_t sqr(__int128_t x) { return x * x; }
int main() {
    n = read(), type = read();
    register long long i, j, l, r, t;
    if (type) {
        register long long x, y, z, m, p;
        read(x), read(y), read(z), read(a[1]), read(a[2]), read(m);
        for (i = 3; i <= n; ++i) a[i] = (x * a[i - 1] + y * a[i - 2] + z) & V;
        for (i = j = 1; i <= m; ++i) {
            read(p), read(l), read(r);
            t = r - l + 1;
            for (; j <= p; ++j) a[j] = a[j] % (r - l + 1) + l;
        }
    } else {
        for (i = 1; i <= n; ++i) read(a[i]);
    }
    for (i = 2; i <= n; ++i) a[i] += a[i - 1];
    l = r = 0;
    for (i = 1; i <= n; ++i) {
        while (l < r && len(q[l + 1]) + a[q[l + 1]] <= a[i]) ++l;
        f[i] = q[l];
        while (l <= r && len(q[r]) + a[q[r]] >= len(i) + a[i]) --r;
        q[++r] = i;
    }
    register __int128_t ans = 0;
    for (i = n; i; i = f[i]) ans += sqr(len(i));
    int ch[50], cnt = 0;
    while (ans) ch[++cnt] = ans % 10, ans /= 10;
    while (cnt) std::cout << ch[cnt--];
    std::cout << std::endl;
    return 0;
}