#include <bits/stdc++.h>
const int N = 200005;
char opt[10];
int cnt, n, q, x;
int dfn[N], lazy[N], sum[N], udf[N], en[N], up[N], head[N],
    next[N], to[N], fa[N], isl[N], size[N], son[N], deep[N];
void insert(int, int);
void dfs1(int, int);
void dfs2(int, int);
void pushdown(int, int, int);
int update(int, int, int, int = 1, int = 1, int = n);
int updateS(int, int);
inline void insert(int x, int y) {
    ++cnt;
    next[cnt] = head[x];
    head[x] = cnt;
    to[cnt] = y;
}
inline void dfs1(int v, int f) {
    fa[v] = f;
    deep[v] = deep[f] + 1;
    size[v] = 1;
    son[v] = N - 1;
    for (int u = head[v]; u; u = next[u]) {
        dfs1(to[u], v);
        size[v] += size[to[u]];
        if (size[to[u]] > size[son[v]]) {
            son[v] = to[u];
        }
    }
    if (son[v] == N - 1) {
        son[v] = 0;
    }
}
inline void dfs2(int v, int ups) {
    up[v] = ups;
    dfn[v] = ++cnt;
    if (son[v]) {
        dfs2(son[v], ups);
    }
    for (int u = head[v]; u; u = next[u]) {
        if (to[u] == son[v]) {
            continue;
        }
        dfs2(to[u], to[u]);
    }
    en[v] = cnt;
}
inline void pushdown(int v, int l, int r) {
    if (!isl[v]) {
        return;
    }
    int mid = (l + r) >> 1;
    isl[v] = 0;
    isl[v << 1] = isl[v << 1 | 1] = 1;
    lazy[v << 1] = lazy[v << 1 | 1] = lazy[v];
    sum[v << 1] = (mid - l + 1) * lazy[v];
    sum[v << 1 | 1] = (r - mid) * lazy[v];
}
inline void pushup(int v) {
    sum[v] = sum[v << 1] + sum[v << 1 | 1];
}
inline int update(int x, int y, int z, int v, int l, int r) {
    if (x > y) {
        std::swap(x, y);
    }
    int tmp = 0;//sum[v];
    if (x <= l && r <= y) {
        isl[v] = 1;
        lazy[v] = z;
        tmp = std::abs(sum[v] - (r - l + 1) * z);
        sum[v] = (r - l + 1) * z;
        return tmp;
    }
    int mid = (l + r) >> 1;
    pushdown(v, l, r);
    if (x <= mid) {
        tmp += update(x, y, z, v << 1, l, mid);
    }
    if (y > mid) {
        tmp += update(x, y, z, v << 1 | 1, mid + 1, r);
    }
    pushup(v);
    return tmp;
}
inline int updateS(int x, int y) {
    int tmp = 0;
    while (up[x] != up[y]) {
        if (deep[up[x]] < deep[up[y]]) {
            std::swap(x, y);
        }
        tmp += update(dfn[up[x]], dfn[x], 1);
        x = fa[up[x]];
    }
    if (dfn[x] > dfn[y]) {
        std::swap(x, y);
    }
    return tmp + update(dfn[x], dfn[y], 1);
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        scanf("%d", &x);
        insert(x, i);
    }
    cnt = 0;
    dfs1(0, 0);
    dfs2(0, 0);
    scanf("%d", &q);
    while (q--) {
        scanf("%s %d", opt, &x);
        printf("%d\n", opt[0] == 'i' ? updateS(0, x) :
            update(dfn[x], en[x], 0));
        fflush(stdout);
    }
    return 0;
}