#include <bits/stdc++.h>

using int64 = long long;

const int N = 10000005;
const int M = 50000005;

int n, b, h, t, u, v, l, r;
int vis[N], s[N], fa[N];
int f[M];

inline int mul(int x, int y) { return int64(x) * y % n; }

inline void init() {
    memset(s, 50, sizeof(s));
    for (int i = 1; i < b; ++i) s[i] = 1, f[++t] = i;
    for (int i = 0; i <= n; ++i) fa[i] = i;
}

inline void solve(int u, int l, int r) {
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> b;
    if (n <= b) return std::cout << 1 << std::endl, 0;
    init();
    while (h < t) {
        if (vis[u = f[h++]]) continue;
        vis[u] = 1, v = mul(u, b);
        if (f[v] > f[u]) f[v] = f[u], f[--h] = v;
        l = v + 1, r = v + b - 1;
        r < n ? solve(u, l, r)
              : (l < n ? (solve(u, l, n - 1), solve(u, 0, r - n))
                       : solve(u, 0, r - n));
    }
    return 0;
}