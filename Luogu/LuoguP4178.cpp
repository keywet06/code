#include <bits/stdc++.h>

#define fir first
#define sec second
#define mkp std::make_pair

using pair = std::pair<int, int>;

const int N = 40005;
const int K = 20005;
const int L = K << 2;

int n, x, y, z, k, ans, c, d;
int size[N], key[N], add[N], fre[N];
int sum[L];

std::vector<pair> to[N];

inline void update(int u) { sum[u] = sum[u << 1] + sum[u << 1 | 1]; }

inline void plus(int u, int l, int r, int x, int y) {
    if (l == r) return void(sum[u] += y);
    int mid = l + r >> 1;
    x <= mid ? plus(u << 1, l, mid, x, y) : plus(u << 1 | 1, mid + 1, r, x, y);
    update(u);
}
inline void plus(int x, int y) { plus(1, 0, k, x, y); }

inline int query(int u, int l, int r, int x, int y) {
    if (l >= x && r <= y) return sum[u];
    int mid = l + r >> 1, ret = 0;
    if (x <= mid) ret += query(u << 1, l, mid, x, y);
    if (y > mid) ret += query(u << 1 | 1, mid + 1, r, x, y);
    return ret;
}
inline int query(int x, int y) { return query(1, 0, k, x, y); }

inline void prefind(int u, int f) {
    size[u] = 1;
    for (pair e : to[u]) {
        if (e.fir == f || key[e.fir]) continue;
        prefind(e.fir, u);
        size[u] += size[e.fir];
    }
}

inline void find(int u, int f, int &d, int &s) {
    int r = 1;
    for (pair e : to[u]) {
        if (e.fir == f || key[e.fir]) continue;
        find(e.fir, u, d, s);
        r &= size[e.fir] << 1 <= s;
    }
    if (r &= size[u] << 1 >= s) d = u;
}

inline void solve(int u, int f, int v) {
    if (v > k) return;
    ans += query(0, k - v), add[++c] = fre[++d] = v;
    for (pair e : to[u]) {
        if (e.fir == f || key[e.fir]) continue;
        solve(e.fir, u, v + e.sec);
    }
}

inline void dfs(int u) {
    prefind(u, u);
    find(u, u, u, size[u]);
    for (pair e : to[u]) {
        if (key[e.fir]) continue;
        solve(e.fir, u, e.sec);
        while (c) plus(add[c--], 1);
    }
    ans += query(0, k);
    while (d) plus(fre[d--], -1);
    key[u] = 1;
    for (pair e : to[u]) {
        if (key[e.fir]) continue;
        dfs(e.fir);
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i < n; ++i) {
        std::cin >> x >> y >> z;
        to[x].push_back(mkp(y, z));
        to[y].push_back(mkp(x, z));
    }
    std::cin >> k;
    dfs(1);
    std::cout << ans << std::endl;
    return 0;
}