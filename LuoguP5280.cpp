#include <cstdio>

inline int read() {
    char c = getchar(); int x = 0;
    while (c < '0' || c > '9') { c = getchar(); }
    while (c >= '0' && c <= '9') { x = (x << 1) + (x << 3) + (c & 15); c = getchar(); }
    return x;
}

const int N = 2000005, p = 998244353;

inline int add(int x, int y) { x += y; return x >= p ? x - p : x; }
inline int sub(int x, int y) { x -= y; return x >= 0 ? x : x + p; }

int n, m, k = 1;

struct SegmentTree {
    int f[N], g[N], tf[N], tg[N], sf[N];

    inline void fjksdhf(int u) { sf[u] = add(f[u], add(sf[u << 1], sf[u << 1 | 1])); }
    inline void fjdkshfk(int u, int x) { f[u] = 1ll * f[u] * x % p; tf[u] = 1ll * tf[u] * x % p; sf[u] = 1ll * sf[u] * x % p; }
    inline void fdsf(int u, int x) { g[u] = 1ll * g[u] * x % p; tg[u] = 1ll * tg[u] * x % p; }
    inline void pushDown(int u) {
        if (tf[u] != 1) { fjdkshfk(u << 1, tf[u]); fjdkshfk(u << 1 | 1, tf[u]); tf[u] = 1; }
        if (tg[u] != 1) { fdsf(u << 1, tg[u]); fdsf(u << 1 | 1, tg[u]); tg[u] = 1; }
    }
    void build(int u, int l, int r) {
        g[u] = tf[u] = tg[u] = 1; 
        if (l == r) { return; } int mid = l + r >> 1;
        build(u << 1, l, mid); build(u << 1 | 1, mid + 1, r);
    }
    void modify(int u, int l, int r, int pl, int pr) {
        pushDown(u);
        if (l == pl && r == pr) {
            f[u] = add(f[u], k); 
            fjdkshfk(u << 1, 2); fjdkshfk(u << 1 | 1, 2); 
        } else {
            int mid = l + r >> 1, ul = u << 1, ur = ul | 1;
            g[u] = add(g[u], k); 
            if (pr <= mid) {
                modify(ul, l, mid, pl, pr); pushDown(ur);
                f[ur] = add(f[ur], sub(k, g[ur])); g[ur] = add(g[ur], g[ur]); 
                fjdkshfk(ur << 1, 2); fjdkshfk(ur << 1 | 1, 2);
                fdsf(ur << 1, 2); fdsf(ur << 1 | 1, 2); 
                fjksdhf(ur);
            } else if (pl > mid) {
                modify(ur, mid + 1, r, pl, pr); pushDown(ul);
                f[ul] = add(f[ul], sub(k, g[ul])); g[ul] = add(g[ul], g[ul]); 
                fjdkshfk(ul << 1, 2); fjdkshfk(ul << 1 | 1, 2);
                fdsf(ul << 1, 2); fdsf(ul << 1 | 1, 2); 
                fjksdhf(ul);
            } else {
                modify(ul, l, mid, pl, mid); modify(ur, mid + 1, r, mid + 1, pr);
            }
        }
        fjksdhf(u);
    }
} smt;

int main() {
    n = read(); m = read(); smt.build(1, 1, n);
    for (int opt, l, r; m; m--) {
        opt = read();
        if (opt == 1) {
            l = read(); r = read();
            smt.modify(1, 1, n, l, r); k = add(k, k);
        } else { printf("%d\n", smt.sf[1]); }
    }
    return 0;
}