#include <bits/stdc++.h>

using int64 = long long;

const int B = 2;
const int N = 100005;
const int M = 262144;
const int64 INF = 1e12;

struct mat {
    int64 a[B][B];
    inline mat() { memset(a, 0, sizeof(a)); }
    inline mat(int64 x, int64 y, int64 z, int64 w) {
        a[0][0] = x, a[0][1] = y, a[1][0] = z, a[1][1] = w;
    }
    inline int64 *operator[](size_t x) { return a[x]; }
};

inline mat operator*(mat a, mat b) {
    return mat(std::min(a[0][0] + b[0][0], a[0][1] + b[1][0]),
               std::min(a[0][0] + b[0][1], a[0][1] + b[1][1]),
               std::min(a[1][0] + b[0][0], a[1][1] + b[1][0]),
               std::min(a[1][0] + b[0][1], a[1][1] + b[1][1]));
}

int a[N], b[N], c[N];

inline mat ope(int x) {
    return mat(a[x] + b[x], std::min(a[x], b[x]), a[x] + b[x] + c[x],
               std::min(a[x] + b[x], std::min(a[x], b[x]) + c[x]));
}

inline mat base(int x) { return mat(0, INF, c[x], INF); }

mat p[M];

inline void build(int u, int l, int r) {
    if (l == r) return void(p[u] = ope(l));
    int mid = l + r >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    p[u] = p[u << 1 | 1] * p[u << 1];
}

inline void update(int u, int l, int r, int x) {
    if (l == r) return void(p[u] = ope(l));
    int mid = l + r >> 1;
    x <= mid ? update(u << 1, l, mid, x) : update(u << 1 | 1, mid + 1, r, x);
    p[u] = p[u << 1 | 1] * p[u << 1];
}

inline mat query(int u, int l, int r, int x, int y) {
    if (l >= x && r <= y) return p[u];
    int mid = l + r >> 1;
    if (y <= mid) {
        return query(u << 1, l, mid, x, y);
    } else if (x > mid) {
        return query(u << 1 | 1, mid + 1, r, x, y);
    }
    return query(u << 1 | 1, mid + 1, r, x, y) * query(u << 1, l, mid, x, y);
}

int n, m, k, s, t;

int main() {
    freopen("plan.in", "r", stdin);
    freopen("plan.out", "w", stdout);
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 2; i <= n; ++i) std::cin >> a[i];
    for (int i = 2; i <= n; ++i) std::cin >> b[i];
    for (int i = 1; i <= n; ++i) std::cin >> c[i];
    if (n > 1) build(1, 2, n);
    for (int i = 1; i <= m; ++i) {
        std::cin >> k >> s >> t;
        if (k == 1) {
            if (s == t && (std::cout << c[s] << '\n', 1)) continue;
            std::cout << (query(1, 2, n, s + 1, t) * base(s))[1][0] << '\n';
        } else if (k == 2) {
            a[s + 1] = t, update(1, 2, n, s + 1);
        } else if (k == 3) {
            b[s + 1] = t, update(1, 2, n, s + 1);
        } else {
            c[s] = t;
            if (s > 1) update(1, 2, n, s);
        }
    }
    return 0;
}