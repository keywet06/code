#include <bits/stdc++.h>
const int N = 300000;
const int M = 600000;
int n, root, pu, pv, cnt;
int head[N], size[N], maxs[N], tree[N];
int next[M], to[M];
long long ans;
inline int lowbit(int x) { return x & (-x); }
inline void update(int x, int v) {
    while (x <= n) tree[x] += v, x += lowbit(x);
}
inline int query(int x) {
    x = std::max(x, 0);
    int ans = 0;
    while (x) ans += tree[x], x &= x - 1;
    return ans;
}
inline int query(int l, int r) { return query(r) - query(l - 1); }
inline void insert(int u, int v) {
    next[++cnt] = head[u];
    head[u] = cnt;
    to[cnt] = v;
}
inline void addedge(int u, int v) {
    insert(u, v);
    insert(v, u);
}
inline void dfs1(int u, int f) {
    int flag = 1;
    size[u] = 1;
    for (int e = head[u]; e; e = next[e]) {
        if (to[e] == f) continue;
        dfs1(to[e], u);
        flag &= size[to[e]] <= n / 2;
        size[u] += size[to[e]];
    }
    flag &= n - size[u] <= n / 2;
    if (flag) root = u;
}
inline void dfs2(int u, int f) {
    size[u] = 1, maxs[u] = 0;
    for (int e = head[u]; e; e = next[e]) {
        if (to[e] == f) continue;
        dfs2(to[e], u);
        size[u] += size[to[e]];
        maxs[u] = std::max(maxs[u], size[to[e]]);
        if (u != root) continue;
        if (size[u] > size[pv]) pv = pu;
        if (size[pv] > size[pu]) std::swap(pv, pu);
    }
}
inline void dfs3(int u, int f) {
    if (u == pu) {
        ans += query(1, n - 2 * size[pu]) * root;
        std::cerr << "Debug: "
                  << "pu + " << query(1, n - 2 * size[pu]) * root << std::endl;
        ans -= query(1, n - 2 * size[pv]) * root;
        std::cerr << "Debug: "
                  << "pv - " << query(1, n - 2 * size[pv]) * root << std::endl;
    }
    ans += query(n - 2 * size[u], n - 2 * maxs[u]) * u;
    std::cerr << "Debug: " << u << " + "
              << query(n - 2 * size[u], n - 2 * maxs[u]) * u << std::endl;
    for (int e = head[u]; e; e = next[e]) {
        if (to[e] != f) dfs3(to[e], u);
    }
    ans -= query(n - 2 * size[u], n - 2 * maxs[u]) * u;
    std::cerr << "Debug: " << u << " - "
              << query(n - 2 * size[u], n - 2 * maxs[u]) * u << std::endl;
    if (u == pu) {
        ans -= query(1, n - 2 * size[pu]) * root;
        std::cerr << "Debug: "
                  << "pu - " << query(1, n - 2 * size[pu]) * root << std::endl;
        ans += query(1, n - 2 * size[pv]) * root;
        std::cerr << "Debug: "
                  << "pv + " << query(1, n - 2 * size[pv]) * root << std::endl;
    }
    update(size[u], u != root);
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i < n; ++i) std::cin >> pu >> pv, addedge(pu, pv);
    dfs1(1, 0);
    dfs2(root, 0);
    dfs3(root, 0);
    ans += query(1, n - 2 * size[pu]) * root;
    for (int u = 1; u <= n; ++u) {
        ans += (u != root) * query(n - 2 * size[u], n - 2 * maxs[u]) * u;
    }
    std::cout << ans << std::endl;
    return 0;
}