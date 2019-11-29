#include <bits/stdc++.h>
const int N = 100005;
int cnt, n, m;
int head[N], next[N], to[N], fa[N], up[N], size[N], son[N], deep[N];
void insert(int, int);
void dfs1(int, int);
void dfs2(int, int);
int lca(int, int);
void update(int, int, int, int);
inline void insert(int x, int y) {
    ++cnt;
    next[cnt] = head[x];
    head[x] = cnt;
    to[cnt] = y;
}
inline void dfs1(int v, int f) {
    fa[v] = f;
    deep[v] = deep[fa[v]] + 1;
    size[v] = 1;
    for (int u = head[v]; u; u = next[u]) {
        dfs1(to[u], v);
        if (size[to[u]] > size[son[v]]) {
            son[v] = to[u];
        }
    }
}
inline void dfs2(int v, int p) {
    up[v] = p;
    if (son[v]) {
        dfs2(son[v], p);
    }
    for (int u = head[v]; u; u = next[u]) {
        if (to[u] == son[v]) {
            continue;
        }
        dfs2(to[u], to[u]);
    }
}
inline int lca(int x, int y) {
    while (up[x] != up[y]) {
        if (deep[up[x]] < deep[up[y]]) {
            std::swap(x, y);
        }
        x = fa[up[x]];
    }
    return deep[x] > deep[y] ? y : x;
}
int main() {
    return 0;
}