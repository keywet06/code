#include <bits/stdc++.h>

using int64 = long long;

const int64 P = 998244353;
const int N = 200005;
const int M = N << 4;

int T, n, m, x, y, c;
int px[N], py[N], p[N];
int plus[M];

int64 ans;
int64 pre[M], inv[M], ire[M];

inline void build(int u, int l, int r) {
    if (l == r) return void(plus[u] = l);
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}

inline void update(int u, int l, int r, int x, int y) {
    if (l >= x && r <= y) return void(++plus[u]);
    int mid = l + r >> 1;
    if (x <= mid) update(u << 1, l, mid, x, y);
    if (y > mid) update(u << 1 | 1, mid + 1, r, x, y);
}

inline int query(int u, int l, int r, int x) {
    if (l == r) return plus[x];
    int mid = l + r >> 1;
    return plus[u] + (x <= mid ? query(u << 1, l, mid, x)
                               : query(u << 1 | 1, mid + 1, r, x));
}

inline int64 C(int m, int n) { return pre[m] * ire[n] % P * ire[m - n] % P; }

inline int64 G(int m, int n) { return C(m + n - 2, m - 1); }

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> T;
    pre[0] = inv[0] = inv[1] = ire[0] = 1;
    for (int i = 1; i < M; ++i) pre[i] = pre[i - 1] * i % P;
    for (int i = 2; i < M; ++i) inv[i] = (P - P / i) * inv[P % i] % P;
    for (int i = 1; i < M; ++i) ire[i] = ire[i - 1] * inv[i] % P;
    while (T--) {
        std::cin >> n >> m;
        for (int i = 1; i <= m; ++i) std::cin >> px[i] >> py[i];
        build(1, 1, n);
        for (int i = m; i; --i) {
            px[i] = query(1, 1, n, px[i]);
            py[i] = query(1, 1, n, py[i]);
            update(1, 1, n, py[i], n);
        }
        p[c = 1] = m;
        for (int i = m - 1; i; --i) {
            if (py[i] < py[p[c]]) p[++c] = i;
        }
        ans = G(n, n);
        for (int i = 1; i <= c; ++i) ans -= G(n, n - (px[p[i]] - py[p[i]] + 1));
        for (int i = 1; i < c; ++i) {
            if (px[i + 1] <= py[i]) continue;
            // ans += G(n, n - (px[]))
        }
    }
    return 0;
}

/*

C(n + n - px[p[i]] - 3 + py[p[i]], n - 1)

C(n + n - px[p[i]] - 3, n - 1) * 
                        _
                        c
  (n + n - px[p[i]] - 3)
---------------------------
                      _
                      c
    (n - px[p[i]] - 1)


*/