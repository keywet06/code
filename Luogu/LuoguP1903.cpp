#include <bits/stdc++.h>

const int N = 150005;

char c;

int n, m, cnt, tot, x, y, S, T, now, l, r, ti;
int a[N], t[N], w[N], rx[N], ry[N], id[N], rt[N], rc[N], ru[N], rs[N], tp[N],
    as[N];

inline void getcs() {
    c = getchar();
    while (c != 'Q' && c != 'R') c = getchar();
}

inline int mi(int x) { return x / S; }
inline int mb(int x) { return x * S; }
inline int me(int x) { return x * S + S; }
inline int nb(int x) { return mb(mi(x)); }
inline int ne(int x) { return me(mi(x)); }

inline void incx(int x) { now += !w[x]++; }
inline void decx(int x) { now -= !--w[x]; }
inline void incl() { decx(l++); }
inline void decl() { incx(l--); }
inline void incr() { incx(r++); }
inline void decr() { decx(r--); }
inline void inct() {
    if (l <= rc[++ti] && rc[ti] <= r) decx(rs[ti]), incx(ru[ti]);
    w[rc[ti]] = ru[ti];
}
inline void dect() {
    if (l <= rc[--ti] && rc[ti] <= r) decx(ru[ti]), incx(rs[ti]);
    w[rc[ti]] = rs[ti];
}
inline void update(int nl, int nr, int nt) {
    while (l > nl) decl();
    while (r < nr) incr();
    while (l < nl) incl();
    while (r > nr) decr();
    while (ti < nt) inct();
    while (ti > nt) dect();
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) std::cin >> a[i], tp[i] = a[i];
    for (int i = 1; i <= m; ++i) {
        getcs(), std::cin >> x >> y;
        if (c == 'Q') {
            rx[++tot] = x, ry[tot] = y, rt[tot] = cnt, id[tot] = tot;
        } else {
            rc[++cnt] = x, ru[cnt] = y, rs[cnt] = tp[x], tp[x] = y;
        }
    }
    S = std::max(int(pow(n * cnt, 1.0 / 3)), 3);
    T = (n - 1) / S + 1;
    std::sort(id + 1, id + tot + 1, [](int x, int y) {
        return mi(rx[x]) != mi(rx[y])
                   ? mi(rx[x]) < mi(ry[y])
                   : (mi(ry[x]) == mi(ry[y]) ? rt[x] < rt[y]
                                             : mi(ry[x]) < mi(ry[y]));
    });
    l = 1, r = 0, ti = 0;
    for (int i = 1; i <= m; ++i) {
        update(rx[id[i]], ry[id[y]], rt[id[i]]);
        as[id[i]] = now;
    }
    for (int i = 1; i <= m; ++i) std::cout << as[i] << '\n';
    return 0;
}