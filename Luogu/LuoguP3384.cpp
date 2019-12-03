#include <bits/stdc++.h>
const int N = 300005;
int CLOCK, cnt, n, m, r, p, opt, x, y;
int head[N], next[N], to[N], fa[N], dfn[N], size[N], son[N], up[N], lst[N], udfn[N], deep[N];
long long z;
long long a[N], val[N], plus[N];
void insert(int, int);
void addedge(int, int);
void dfs1(int, int);
void dfs2(int, int);
void updata(int);
void pushdown(int, int, int);
void build(int, int, int);
long long query(int, int, int, int, int);
void change(int, int, int, long long, int, int);
long long queryS(int, int);
void changeS(int, int, long long);
int main() {
    scanf("%d %d %d %d", &n, &m, &r, &p);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
    }
    for (int i = 1; i < n; ++i) {
        scanf("%d %d", &x, &y);
        addedge(x, y);
    }
    dfs1(r, r);
    fprintf(stderr, "Debug: OK!\n");
    dfs2(r, r);
    build(1, 1, n);
    for (int i = 1; i <= m; ++i) {
        scanf("%d", &opt);
        if (opt == 1) {
            scanf("%d %d %lld", &x, &y, &z);
            changeS(x, y, z);
        } else if (opt == 2) {
            scanf("%d %d", &x, &y);
            printf("%lld\n", queryS(x, y));
        } else if (opt == 3) {
            scanf("%d %lld", &x, &z);
            change(1, dfn[x], lst[x], z, 1, n);
        } else {
            scanf("%d", &x);
            printf("%lld\n", query(1, dfn[x], lst[x], 1, n));
        }
    }
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
    deep[v] = deep[f] + 1;
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
    for (int u = head[v]; u; u = next[u]) {
        if (to[u] == fa[v] || to[u] == son[v]) {
            continue;
        }
        dfs2(to[u], to[u]);
    }
    lst[v] = CLOCK;
}
inline void updata(int v) {
    (val[v] = val[v << 1] + val[v << 1 | 1]) %= p;
}
inline void pushdown(int v, int l, int r) {
    int mid = (l + r) >> 1;
    (val[v << 1] += plus[v] * (mid - l + 1)) %= p;
    (val[v << 1 | 1] += plus[v] * (r - mid)) %= p;
    (plus[v << 1] += plus[v]) %= p;
    (plus[v << 1 | 1] += plus[v]) %= p;
    plus[v] = 0;
}
inline void build(int v, int l, int r) {
    if (l == r) {
        val[v] = a[udfn[l]];
        return;
    }
    int mid = (l + r) >> 1;
    build(v << 1, l, mid);
    build(v << 1 | 1, mid + 1, r);
    updata(v);
}
inline long long query(int v, int x, int y, int l, int r) {
    if (x <= l && r <= y) {
        return val[v];
    }
    int mid = (l + r) >> 1;
    pushdown(v, l, r);
    return ((x <= mid ? query(v << 1, x, y, l, mid) : 0) + (y > mid ? query(v << 1 | 1, x, y, mid + 1, r) : 0)) % p;
}
inline void change(int v, int x, int y, long long z, int l, int r) {
    if (x <= l && r <= y) {
        (val[v] += z * (r - l + 1)) %= p;
        (plus[v] += z) %= p;
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(v, l, r);
    if (x <= mid) {
        change(v << 1, x, y, z, l, mid);
    }
    if (y > mid) {
        change(v << 1 | 1, x, y, z, mid + 1, r);
    }
    updata(v);
}
inline long long queryS(int x, int y) {
    long long tmp = 0;
    while (up[x] != up[y]) {
        if (deep[up[x]] < deep[up[y]]) {
            std::swap(x, y);
        }
        (tmp += query(1, dfn[up[x]], dfn[x], 1, n)) %= p;
        x = fa[up[x]];
    }
    if (dfn[x] > dfn[y]) {
        std::swap(x, y);
    }
    return (tmp + query(1, dfn[x], dfn[y], 1, n)) % p;
}
inline void changeS(int x, int y, long long z) {
    while (up[x] != up[y]) {
        if (deep[up[x]] < deep[up[y]]) {
            std::swap(x, y);
        }
        change(1, dfn[up[x]], dfn[x], z, 1, n);
        x = fa[up[x]];
    }
    if (dfn[x] > dfn[y]) {
        std::swap(x, y);
    }
    change(1, dfn[x], dfn[y], z, 1, n);
}