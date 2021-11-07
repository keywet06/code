#include <bits/stdc++.h>

using int64 = long long;

const int N = 1e5 + 5;
const int M = 1e6 + 5;

int n, m, pl, pr;
int a[N];

int64 sum, INF;
int64 num[M];
int64 _f[N], _g[N], *f = _f, *g = _g;

inline void add(const int x) { sum += x * (num[x]++ << 1 | 1); }
inline void del(const int x) { sum -= x * (--num[x] << 1 | 1); }

inline void fit(const int l, const int r) {
    while (pl < l) del(a[pl++]);
    while (pl > l) add(a[--pl]);
    while (pr < r) add(a[++pr]);
    while (pr > r) del(a[pr--]);
}

inline void solve(int l, int r, int ql, int qr) {
    if (l > r) return;
    int m = l + r >> 1, qm;
    int64 &ret = f[m] = (fit(ql, m), INF);
    while (pl <= qr && pl <= m) {
        if (g[pl - 1] + sum < ret) ret = g[pl - 1] + sum, qm = pl;
        del(a[pl++]);
    }
    solve(l, m - 1, ql, qm), solve(m + 1, r, qm, qr);
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    memset(f, 63, sizeof(_f));
    memset(g, 63, sizeof(_g));
    INF = f[0], f[0] = g[0] = 0;
    while (m--) solve(1, n, 1, n), std::swap(f, g);
    std::cout << g[n] << std::endl;
    return 0;
}