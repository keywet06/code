#include <bits/stdc++.h>
const int N = 100005;
int CLOCK, cnt, m, n, root, mod, x, y, z;
int a[N], dfn[N], par[N], head[N], next[N], to[N], son[N], size[N], sum[N], deep[N], top[N];
void insert(int, int);
void addedge(int, int);
void dfs1(int = root, int = root);
void dfs2(int = root, int = root);
void pushup(int, int, int);
void build(int = root, int = 1, int = n);
void update(int, int, int, int = root, int = 1, int = n);
int query(int, int, int = root, int = 1, int = n);
void uppath(int, int, int);
int querypath(int, int);
int main() {
    scanf("%d %d %d %d", &n, &m, &root, &mod);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i < n; ++i) {
        scanf("%d %d", &x, &y);
        addedge(x, y);
    }
    dfs1();
    dfs2();
    build();
    for (int i = 1; i <= m; ++i) {
        scanf("%d", x);
        if (x == 1) {
            scanf("%d %d %d", &x, &y, &z);
            uppath(x, y, z);
        } else if (x == 2) {
            scanf("%d %d", &x, &y);
            printf("%d\n", querypath(x, y));
        } else if (x == 3) {
            scanf("%d %d", &x, &y);
            update(dfn[x], dfn[par[x]], y);
        } else if (x == 4) {
            scanf("%d", &x);
            printf("%d\n", query(dfn[x], dfn[par[x]]));
        }
    }
    return 0;
}
inline void insert(int x, int y) {
    ++cnt;
    to[cnt] = head[x];
    head[x] = cnt;
    to[cnt] = y;
}
inline void addedge(int x, int y) {
    insert(x, y);
    insert(y, x);
}
inline void dfs1(int v, int p) {
    par[v] = p;
    son[v] = 0;
    size[v] = 1;
    deep[v] = deep[p] + 1;
    for (int u = head[v]; u; u = next[u]) {
        if (to[u] == p) {
            continue;
        }
        dfs1(to[u], v);
        size[v] += size[to[u]];
        if (size[to[u]] > size[son[v]]) {
            son[v] = to[u];
        }
    }
}
inline void dfs2(int v, int p) {
    dfn[v] = ++CLOCK;
    top[v] = p;
    if (son[v]) {
        dfs2(son[v], p);
    }
    for (int u = head[v]; u; u = next[u]) {
        if (to[u] == )
    }
}