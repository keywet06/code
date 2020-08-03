#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
const int N = 5005;
int n, k, x, y, z;
int fa[N], deep[N], top[N], son[N], size[N];
int dis[N][N];
std::vector<std::pair<int, int> > to[N];
inline void dfs1(int u, int f) {
    fa[u] = f;
    size[u] = 1;
    for (auto v : to[u]) {
        if (v.first == f) continue;
        deep[v.first] = deep[u] + v.second;
        dfs1(v.first, u);
        size[u] += size[v.first];
        if (size[v.first] > size[son[u]]) son[u] = v.first;
    }
}
inline void dfs2(int u, int t) {
    top[u] = t;
    if (son[u]) dfs2(son[u], t);
    for (auto v : to[u]) {
        if (v.first == fa[u] || v.first == son[u]) continue;
        dfs2(v.first, v.first);
    }
}
inline int lca(int x, int y) {
    while (top[x] != top[y]) {
        if (deep[top[x]] < deep[top[y]]) std::swap(x, y);
        x = fa[top[x]];
    }
    return deep[x] < deep[y] ? x : y;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> k;
    for (int i = 1; i < n; ++i) {
        std::cin >> x >> y >> z;
        to[x].push_back(std::make_pair(y, z));
        to[y].push_back(std::make_pair(x, z));
    }
    dfs1(1, 1);
    dfs2(1, 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            dis[i][j] = dis[j][i] = deep[i] + deep[j] - 2 * deep[lca(i, j)];
        }
    }
    for (int i = 1; i <= n; ++i) {
        std::sort(dis[i] + 1, dis[i] + n + 1);
        std::cout << dis[i][k] << '\n';
    }
    return 0;
}