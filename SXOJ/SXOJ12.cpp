#include <bits/stdc++.h>

using int64 = long long;

const int N = 300005;
const int M = 1048576;
const int C = 45;

int n, q, o, x, y, z;
int a[N];
int equ[M];

int64 val[M], min[M], mus[M];

inline void pushup(int u) {
    // if (equ[u << 1] && equ[u << 1 | 1] && val[u << 1] == val[u << 1 | 1] &&
    //     min[u << 1] == min[u << 1 | 1]) {
    //     equ[u] = 1, val[u] = val[u << 1], min[u] = min[u << 1];
    //     return;
    // }
    equ[u] = 0, min[u] = std::min(min[u << 1], min[u << 1 | 1]);
}

inline void build(int u, int l, int r) {
    if (l == r) {
        equ[u] = val[u] = 1;
        while (val[u] < a[l]) val[u] *= C;
        min[u] = val[u] - a[l];
        return;
    }
    int mid = l + r >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    min[u] = std::min(min[u << 1], min[u << 1 | 1]);
}

inline void pushdown(int u) {
    if (equ[u]) {
        equ[u << 1] = equ[u << 1 | 1] = equ[u];
        min[u << 1] = min[u << 1 | 1] = min[u];
        val[u << 1] = val[u << 1 | 1] = val[u];
        mus[u << 1] = mus[u << 1 | 1] = mus[u];
        mus[u] = 0;
        return;
    }
    if (!mus[u]) return;
    mus[u << 1] += mus[u], mus[u << 1 | 1] += mus[u];
    min[u << 1] -= mus[u], min[u << 1 | 1] -= mus[u];
    mus[u] = 0;
}

inline void modify(int u, int l, int r, int x, int y, int64 v, int64 d) {
    if (l >= x && r <= y) {
        return void((equ[u] = 1, val[u] = v, min[u] = d, mus[u] = 0));
    }
    int mid = l + r >> 1;
    pushdown(u);
    if (x <= mid) modify(u << 1, l, mid, x, y, v, d);
    if (y > mid) modify(u << 1 | 1, mid + 1, r, x, y, v, d);
    pushup(u);
}

inline void plus(int u, int l, int r, int x, int y, int64 z) {
    if (l >= x && r <= y) return void((min[u] -= z, mus[u] += z));
    int mid = l + r >> 1;
    pushdown(u);
    if (x <= mid) plus(u << 1, l, mid, x, y, z);
    if (y > mid) plus(u << 1 | 1, mid + 1, r, x, y, z);
    pushup(u);
}

inline void change(int u, int l, int r) {
    if (min[u] >= 0) return;
    if (l == r) {
        while (min[u] < 0) min[u] -= val[u], val[u] *= C, min[u] += val[u];
        return;
    }
    int mid = l + r >> 1;
    pushdown(u);
    change(u << 1, l, mid);
    change(u << 1 | 1, mid + 1, r);
    pushup(u);
}

inline int64 query(int u, int l, int r, int x) {
    if (l == r) return val[u] - min[u];
    int mid = l + r >> 1;
    pushdown(u);
    return x <= mid ? query(u << 1, l, mid, x)
                    : query(u << 1 | 1, mid + 1, r, x);
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> q;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    build(1, 1, n);
    while (q--) {
        std::cin >> o;
        if (o == 1) {
            std::cin >> x, std::cout << query(1, 1, n, x) << '\n';
        } else if (o == 2) {
            std::cin >> x >> y >> z;
            int64 v = 1;
            while (v < z) v *= C;
            modify(1, 1, n, x, y, v, v - z);
        } else if (o == 3) {
            std::cin >> x >> y >> z;
            do {
                plus(1, 1, n, x, y, z);
                change(1, 1, n);
            } while (!min[1]);
        }
    }
    return 0;
}