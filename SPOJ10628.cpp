#include <bits/stdc++.h>
const int N = 400005;
const int Z = 40000005;
class Node {
   public:
    int size, lson, rson;
};
int cnt, vnt, n, m, x, y, z;
int a[N], head[N], next[N], to[N], fa[N], up[N], size[N], son[N], deep[N],
  tree[N], b[N], c[N];
Node node[Z];
void insert(int, int);
void addedge(int, int);
void dfs1(int, int);
void dfs2(int, int);
int lca(int, int);
void update(int, int, int = 1, int = vnt);
int query(int, int, int, int, int, int = 1, int = vnt);
inline void insert(int x, int y) {
    ++cnt;
    next[cnt] = head[x];
    head[x] = cnt;
    to[cnt] = y;
}
inline void addedge(int x, int y) {
    insert(x, y);
    insert(y, x);
}
inline void dfs1(int v, int f) {
    fa[v] = f;
    deep[v] = deep[fa[v]] + 1;
    size[v] = 1;
    node[tree[v] = ++cnt] = node[tree[fa[v]]];
    update(tree[v], c[v]);
    for (int u = head[v]; u; u = next[u]) {
        if (to[u] == fa[v]) {
            continue;
        }
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
        if (to[u] == fa[v] || to[u] == son[v]) {
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
inline void update(int v, int x, int l, int r) {
    ++node[v].size;
    if (l == r) {
        return;
    }
    int mid = l + r >> 1;
    if (x <= mid) {
        node[++cnt] = node[node[v].lson];
        update(node[v].lson = cnt, x, l, mid);
    } else {
        node[++cnt] = node[node[v].rson];
        update(node[v].rson = cnt, x, mid + 1, r);
    }
}
inline int query(int v1, int v2, int v3, int v4, int k, int l, int r) {
    if (l == r) {
        return l;
    }
    int mid = l + r >> 1, tmp = node[node[v1].lson].size + node[node[v2].lson].size
      - node[node[v3].lson].size - node[node[v4].rson].size;
    if (k <= tmp) {
        return query(node[v1].lson, node[v2].lson, node[v3].lson, node[v4].rson
          , k, l, mid);
    } else {
        return query(node[v1].rson, node[v2].rson, node[v3].rson, node[v4].rson
          , k - tmp, mid + 1, r);
    }
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        b[i] = a[i];
    }
    std::sort(b + 1, b + n + 1);
    vnt = std::unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1; i <= n; ++i) {
        c[i] = std::lower_bound(b + 1, b + vnt + 1, a[i]) - b;
    }
    for (int i = 1; i < n; ++i) {
        std::cin >> x >> y;
        addedge(x, y);
    }
    tree[0] = cnt = 1;
    dfs1(1, 0);
    dfs2(1, 1);
    for (int i = 1; i <= m; ++i) {
        std::cin >> x >> y >> z;
        std::cout <<
          b[query(tree[x], tree[y], tree[lca(x, y)], tree[fa[lca(x, y)]], z)]
          << std::endl;
    }
    return 0;
}