#include <bits/stdc++.h>

struct emptystream {
    template <typename _Tp>
    emptystream &operator<<(_Tp x) { return *this; }
} emp;

#define Deb std::cerr
#define Delin Deb << "[Debug] at Line " << __LINE__
#define Debug Delin << " : "
#define Deline Delin << '\n'

using int64 = long long;

const int D = 1000000;
const int N = 1 << 20;
const int M = N << 1;

template <typename _Tp1, typename _Tp2>
inline _Tp1 &mid(_Tp1 &x, const _Tp2 y) {
    return x < y ? x : (x = y);
}

template <typename _Tp1, typename _Tp2, typename... Args>
inline _Tp1 &mid(_Tp1 &x, const _Tp2 y, const Args... args) {
    return mid(mid(x, y), args...);
}

struct node {
    int64 k, b;
    node(){};
    node(int64 _k, int64 _b) : k(_k), b(_b) {}
    node(int64 _k, int64 x, int64 y) : k(_k), b(y - x * _k) {}
    int64 get(int64 x) { return k * x + b; }
};

bool h[M];

int n, k;

int64 A, B, x, y, z, ans;
int64 sa[N], l[N], r[N];

node da, db, dc;
node d[M];

inline void build(int u, int l, int r) {
    if (l == r) return h[u] = true, d[u].b = sa[l], void(0);
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}

inline node &query(int u, int l, int r, int x) {
    if (h[u]) return d[u];
    int mid = l + r >> 1;
    return x <= mid ? query(u << 1, l, mid, x)
                    : query(u << 1 | 1, mid + 1, r, x);
}

inline int64 query(int x) { return query(1, 1, D, x).get(x); }

inline int64 meet(node a, node b) {
    Debug << "meet(" << a.k << "x + " << a.b << ", " << b.k << "x + " << b.b
          << ") returns " << (b.b - a.b) / (a.k - b.k) << '\n';
    return (b.b - a.b) / (a.k - b.k);
}

inline void update(int u, int l, int r, int x, int y, node nd) {
    if (l >= x && r <= y) return h[u] = true, d[u] = nd, void(0);
    int mid = l + r >> 1;
    if (h[u]) {
        h[u] = false, h[u << 1] = h[u << 1 | 1] = true;
        d[u << 1] = d[u << 1 | 1] = d[u];
    }
    if (x <= mid) update(u << 1, l, mid, x, y, nd);
    if (y > mid) update(u << 1 | 1, mid + 1, r, x, y, nd);
}

inline void update(int x, int y, node nd) {
    Debug << "update(" << x << ", " << y << ", " << nd.k << "x + " << nd.b
          << ")" << '\n';
    x = std::max(x, 1), y = std::min(y, D);
    if (x <= y) update(1, 1, D, x, y, nd);
}

inline void getans(int u, int l, int r) {
    if (h[u]) return void(mid(ans, d[u].get(l), d[u].get(r)));
    int mid = l + r >> 1;
    getans(u << 1, l, mid);
    getans(u << 1 | 1, mid + 1, r);
}

inline void out(int u, int l, int r) {
    if (h[u] && l <= 30) {
        for (int i = l; i <= r && i <= 30; ++i) Deb << d[u].get(i) << ' ';
    }
    if (h[u]) return;
    int mid = l + r >> 1;
    out(u << 1, l, mid);
    out(u << 1 | 1, mid + 1, r);
}

inline void out() { Debug, out(1, 1, D), Deb << '\n'; }

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> A >> B;
    std::cin >> k;
    for (int i = 1; i <= k; ++i) std::cin >> l[i] >> r[i];
    for (int i = 1; i < l[1]; ++i) sa[l[1] - i] = A * i;
    for (int i = r[k] + 1; i <= D; ++i) sa[i] = B * (i - r[k]);
    for (int i = 1; i < k; ++i) {
        x = meet(node(B, r[i], 0), node(-A, l[i + 1], 0));
        y = std::min(x, l[i + 1]);
        for (int j = r[i] + 1; j < y; ++j) sa[j] = B * (j - r[i]);
        y = std::max(x, r[i]), z = l[i + 1];
        for (int j = y + 1; j < z; ++j) sa[j] = A * (z - j);
    }
    build(1, 1, D);
    for (int i = 2; i <= n; ++i) {
        Debug << "Start#" << i << '\n';
        out();
        std::cin >> k;
        for (int j = 1; j <= k; ++j) std::cin >> l[j] >> r[j];
        update(1, l[1], node(-A, l[1], query(l[1])));
        for (int j = 1; j < k; ++j) {
            da = node(B, r[j], query(r[j]));
            db = node(-A, l[j + 1], query(l[j + 1]));
            x = meet(da, db);
            update(r[j] + 1, x, da);
            update(x + 1, l[j + 1] - 1, db);
        }
        update(r[k] + 1, D, node(B, r[k], query(r[k])));
    }
    out();
    std::cout << (ans = 1ll << 60, getans(1, 1, D), ans) << '\n';
    return 0;
}