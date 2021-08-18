#include <bits/stdc++.h>

#define fir first
#define sec second
#define mkp std::make_pair

using pair = std::pair<int, int>;

const int N = 10005;
const int Q = 105;
const int K = 10000005;

bool ans[Q];
bool has[K];

int n, m, x, y, z, c, d;
int key[N], size[N], fre[N], add[N];
int que[Q];

std::vector<pair> to[N];

inline void prefind(int u, int f) {
    size[u] = 1;
    for (pair e : to[u]) {
        if (e.fir == f || key[e.fir]) continue;
        prefind(e.fir, u);
        size[u] += size[e.fir];
    }
}

inline void find(int u, int f, int &d, int &v) {
    int c = 1;
    for (pair e : to[u]) {
        if (e.fir == f || key[e.fir]) continue;
        find(e.fir, u, d, v);
        c &= size[e.fir] << 1 <= v;
    }
    if (c &= size[u] << 1 >= v) d = u;
}

inline void solve(int u, int f, int v) {
    if (v >= K) return;
    for (int i = 1; i <= m; ++i) ans[i] |= v <= que[i] && has[que[i] - v];
    add[++d] = fre[++c] = v;
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
        while (d) has[add[d--]] = 1;
    }
    for (int i = 1; i <= m; ++i) ans[i] |= has[que[i]];
    while (c) has[fre[c--]] = 0;
    key[u] = 1;
    for (pair e : to[u]) {
        if (key[e.fir]) continue;
        dfs(e.fir);
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 1; i < n; ++i) {
        std::cin >> x >> y >> z;
        to[x].push_back(mkp(y, z));
        to[y].push_back(mkp(x, z));
    }
    for (int i = 1; i <= m; ++i) std::cin >> que[i];
    dfs(1);
    for (int i = 1; i <= m; ++i) std::cout << (ans[i] ? "AYE\n" : "NAY\n");
    return 0;
}
