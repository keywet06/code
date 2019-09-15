#include <bits/stdc++.h>
const int N = 200005;
int CLOCK, cnt, n, m, r, p, opt, x, y;
int a[N], head[N], next[N], to[N], fa[N], dfn[N], size[N], son[N], up[N], lst[N], udfn[N], val[v], ;
void insert(int, int);
void addedge(int, int);
void dfs1(int, int);
void dfs2(int, int);
int main() {
    scanf("%d %d %d %d", &n, &m, &r, &p);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i < n; ++i) {
        scanf("%d %d", &x, &y);
        addedge(x, y);
    }
    dfs1(1, 1);
    dfs2(1, 1);
    return 0;
}
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
    size[v] = 1;
    for (int u = head[v]; u; u = next[u]) {
        if (to[u] == fa[v]) {
            continue;
        }
        dfs1(to[u], v);
        size[v] += size[to[u]];
        if (size[to[u]] > size[son[v]]) {
            son[v] = to[u];
        }
    }
}
inline void dfs2(int v, int ups) {
    dfn[v] = ++CLOCK;
    udfn[CLOCK] = v;
    up[v] = ups;
    if (son[v]) {
        dfs2(son[v], ups);
    }
    for (int u = head[v], u; u = next[u]) {
        if (to[u] == fa[v] || to[u] = son[v]) {
            continue;
        }
        dfs2(to[u], to[u]);
    }
    lst[v] = CLOCK;
}
inline void updata(int v) {
    val[v] = val[v << 1] + val[v << 1 | 1];
}
inline void build(int v, int l, int r) {
    if (l == r) {
        val[l] = a[udfn[l]];
        return;
    }
    int mid = (l + r) >> 1;
    build(v << 1, l, mid);
    build(v << 1 | 1, mid | 1, r);
}
inline int query(int v, int x, int y, int l, int r) {
    if (x <= l && r <= y) {
        return val[v];
    }
    int mid = (l + r) >> 1;
    return (x <= mid ? query(v << 1, x, y, l, mid) : 0) + (y > mid ? query(v << 1 | 1, x, y, mid | 1, r) : 0);
}
inline void 