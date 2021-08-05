#include <bits/stdc++.h>

const int N = 500005;

int n, q, cnt;
int pu[N], pv[N], pw[N], fi[N], ans[N], fa[N], deep[N], size[N], top[N], dfn[N],
    son[N];

std::vector<int> to[N];

inline int find(int x) { return fi[x] == x ? x : (fi[x] = find(fi[x])); }

inline void dfs1(int u, int f) {
    fa[u] = f, size[u] = 1;
    for (int v : to[u]) {
        if (v == f) continue;
        deep[v] = deep[u] + 1, dfs1(v, u), size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
    
}

inline void dfs2(int u, int c) {}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> q;
    for (int i = 1; i <= n; ++i) fi[i] = i;
    for (int i = 1; i <= q; ++i) {
        std::cin >> pu[i] >> pv[i] >> pw[i];
        if (find(pu[i]) == find(pv[i])) continue;
        ans[i] = 1, fi[find(pu[i])] = find(pv[i]);
        to[pu[i]].push_back(pv[i]);
        to[pv[i]].push_back(pu[i]);
    }
    for (int i = 1; i <= n; ++i) {
    }
    return 0;
}