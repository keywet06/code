#include <bits/stdc++.h>
const int SZ = 1 << 19, N = 3e5 + 9;
char buf[SZ], *ie = buf + SZ, *ip = ie - 1;
int atp;
inline int in() {
    std::cin >> atp;
    return atp;
}
int f[N], c[N][2], v[N], s[N], st[N];
bool r[N];
inline bool nroot(int x) { return c[f[x]][0] == x || c[f[x]][1] == x; }
inline void pushup(int x) { s[x] = s[c[x][0]] ^ s[c[x][1]] ^ v[x]; }
inline void pushr(int x) {
    int t = c[x][0];
    c[x][0] = c[x][1];
    c[x][1] = t;
    r[x] ^= 1;
}
inline void pushdown(int x) {
    if (r[x]) {
        if (c[x][0]) pushr(c[x][0]);
        if (c[x][1]) pushr(c[x][1]);
        r[x] = 0;
    }
}
inline void rotate(int x) {
    int y = f[x], z = f[y], k = c[y][1] == x, w = c[x][!k];
    if (nroot(y)) c[z][c[z][1] == y] = x;
    c[x][!k] = y;
    c[y][k] = w;
    if (w) {
        f[w] = y;
    }
    f[y] = x;
    f[x] = z;
    pushup(y);
}
inline void splay(int x) {
    int y = x, z = 0;
    st[++z] = y;
    while (nroot(y)) st[++z] = y = f[y];
    while (z) pushdown(st[z--]);
    while (nroot(x)) {
        y = f[x];
        z = f[y];
        if (nroot(y)) rotate((c[y][0] == x) ^ (c[z][0] == y) ? x : y);
        rotate(x);
    }
    pushup(x);
}
inline void access(int x) {
    for (int y = 0; x; x = f[y = x]) splay(x), c[x][1] = y, pushup(x);
}
inline void makeroot(int x) {
    access(x);
    splay(x);
    pushr(x);
}
int findroot(int x) {
    access(x);
    splay(x);
    while (c[x][0]) pushdown(x), x = c[x][0];
    splay(x);
    return x;
}
inline void split(int x, int y) {
    makeroot(x);
    access(y);
    splay(y);
}
inline void link(int x, int y) {
    makeroot(x);
    if (findroot(y) != x) f[x] = y;
}
inline void cut(int x, int y) {
    makeroot(x);
    if (findroot(y) == x && f[y] == x && !c[y][0]) {
        f[y] = c[x][1] = 0;
        pushup(x);
    }
}
int main() {
    // std::ios::sync_with_stdio(0);
    // std::cin.tie(0);
    // std::cout.tie(0);
    int rt, n, m, j, k, opt;
    n = in();
    rt = n + 1;
    for (j = 1; j <= rt; ++j) {
        s[j] = 1;
    }
    for (j = 1; j <= n; ++j) {
        k = in();
        f[j] = j + k > n ? rt : j + k;
    }
    m = in();
    while (m--) {
        opt = in();
        if (opt == 1) {
            j = in() + 1;
            access(j);
            splay(j);
            std::cout << s[j] - 1 << std::endl;
        } else {
            j = in() + 1;
            k = in();
            access(j);
            splay(j);
            c[j][0] = f[c[j][0]] = 0;
            f[j] = j + k > n ? rt : j + k;
            pushup(j);
        }
    }
    return 0;
}