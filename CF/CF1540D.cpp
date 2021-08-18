#include <bits/stdc++.h>

using int64 = long long;

const int K = 505;
const int R = 2005;
const int N = 100005;
const int M = 1000005;
const int O = 2000005;
const int64 P = 998244353;

inline int64 read() {
    int64 t = 0;
    char v = getchar();
    while (v < '0') v = getchar();
    while (v >= '0') t = (t << 3) + (t << 1) + v - 48, v = getchar();
    return t;
}

inline void add(int64 &x, int64 y) { (x += y) >= P ? x -= P : x; }

inline int64 ksm(int64 x, int64 y) {
    int64 s = 1;
    while (y) {
        if (y & 1) s = 1ll * s * x % P;
        x = 1ll * x * x % P, y >>= 1;
    }
    return s;
}

struct edge {
    int64 to, next;
} e[O];

int64 t, n, m, ans, cnt, num, bi;
int64 tg[R], mn[R], c[R], pos[R];
int64 blk[N], st[N], ed[N], vis[N], d[N];
int64 a[M], head[M], bl[M];
int64 s[K][K];

inline void pu(int64 p) {
    if (mn[p << 1] < mn[p << 1 | 1]) {
        mn[p] = mn[p << 1], pos[p] = pos[p << 1];
    } else {
        mn[p] = mn[p << 1 | 1], pos[p] = pos[p << 1 | 1];
    }
}
inline void build(int64 p, int64 l, int64 r) {
    if (l == r) {
        mn[p] = c[l], pos[p] = l;
        return;
    }
    int64 mid = l + r >> 1;
    build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
    pu(p);
}
inline void Add(int64 p, int64 x) { tg[p] += x, mn[p] += x; }
inline void pd(int64 p) {
    if (tg[p]) Add(p << 1, tg[p]), Add(p << 1 | 1, tg[p]), tg[p] = 0;
}
inline void cg(int64 p, int64 l, int64 r, int64 x, int64 y) {
    if (l == r) {
        mn[p] = y;
        return;
    }
    pd(p);
    int64 mid = l + r >> 1;
    x <= mid ? cg(p << 1, l, mid, x, y) : cg(p << 1 | 1, mid + 1, r, x, y);
    pu(p);
}

inline void add(int64 p, int64 l, int64 r, int64 x, int64 y) {
    if (l >= x && r <= y) return Add(p, -1);
    pd(p);
    int64 mid = l + r >> 1;
    if (x <= mid) add(p << 1, l, mid, x, y);
    if (y > mid) add(p << 1 | 1, mid + 1, r, x, y);
    pu(p);
}
inline void buildd(int64 p, int64 l, int64 r) {
    memset(tg, 0, sizeof(tg));
    memset(mn, 0, sizeof(mn));
    memset(pos, 0, sizeof(pos));
    for (int64 i = l; i <= r; ++i) c[i - l + 1] = a[i];
    int64 L = r - l + 1;
    build(1, 1, L);
    for (int64 i = 1; i <= r - l + 1; ++i) {
        s[p][i] = mn[1], s[p][i] = std::max(s[p][i], s[p][i - 1]);
        int64 xx = pos[1];
        if (xx ^ L) add(1, 1, L, xx + 1, L);
        cg(1, 1, L, xx, 1e9);
    }
    s[p][d[p] + 1] = 1e9;
}
signed main() {
    n = read(), bi = sqrt(n);
    for (int64 i = 1; i <= n; ++i) a[i] = read(), bl[i] = (i - 1) / bi + 1;
    for (int64 i = 1; i <= n; ++i) {
        if (!st[bl[i]]) st[bl[i]] = i;
        ed[bl[i]] = i;
    }
    for (int64 i = 1; i <= bl[n]; ++i) {
        d[i] = ed[i] - st[i] + 1, buildd(i, st[i], ed[i]);
    }
    m = read();
    while (m--) {
        int64 o = read(), x = read();
        if (o == 1) {
            a[x] = read(), buildd(bl[x], st[bl[x]], ed[bl[x]]);
        } else {
            int64 ans = a[x];
            for (int64 j = x + 1; j <= ed[bl[x]]; ++j) ans += (ans >= a[j]);
            for (int64 j = bl[x] + 1; j <= bl[n]; ++j) {
                int64 pos =
                    std::upper_bound(s[j] + 1, s[j] + d[j] + 2, ans) - s[j];
                ans += pos - 1;
            }
            printf("%d\n", n - ans);
        }
    }
}