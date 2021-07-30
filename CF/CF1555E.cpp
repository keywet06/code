#include <bits/stdc++.h>

using int64 = long long;

const int N = 300005;
const int M = 2100000;
const int64 INF = 100000000000000000;

int n, m;
int l[N], r[N], w[N], p[N];

int64 min[M];

inline void build(int u, int l, int r) {
    if (l == r) return void(min[u] = l == 1 ? 0 : INF);
    int mid = l + r >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    min[u] = std::min(min[u << 1], min[u << 1 | 1]);
}

inline int64 query(int u, int l, int r, int x, int y) {
    if (l >= x && r <= y) return min[u];
    int mid = l + r >> 1;
    int64 ret = INF;
    if (x <= mid) ret = std::min(ret, query(u << 1, l, mid, x, y));
    if (y > mid) ret = std::min(ret, query(u << 1 | 1, mid + 1, r, x, y));
    return ret;
}

inline void update(int u, int l, int r, int x, int64 y) {
    if (l == r) return void(min[u] = std::min(min[u], y));
    int mid = l + r >> 1;
    if (x <= mid) {
        update(u << 1, l, mid, x, y);
    } else {
        update(u << 1 | 1, mid + 1, r, x, y);
    }
    min[u] = std::min(min[u << 1], min[u << 1 | 1]);
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) std::cin >> l[i] >> r[i] >> w[i], p[i] = i;
    std::sort(p + 1, p + n + 1, [](int x, int y) { return r[x] < r[y]; });
    build(1, 1, m);
    for (int i = 1; i <= n; ++i) {
        update(1, 1, m, r[p[i]], query(1, 1, m, l[p[i]], r[p[i]]) + w[p[i]]);
    }
    std::cout << query(1, 1, m, m, m) << std::endl;
    return 0;
}