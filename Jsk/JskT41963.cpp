#include <bits/stdc++.h>
const int N = 1000005;
const int R = 10000005;
class point {
    public:
        int data;
        point *lson, *rson;
};
point po[R];
point *cnt = po;
point *root[N];
int CLOCK, ccnt, m, n, q, x, y, z, l, r, mid, t;
int col[N], head[N], next[N], to[N], dfn[N], udf[N], up[N], deep[N], son[N],
    size[N], fa[N];
void insert(int, int);
void addedge(int, int);
void dfs1(int, int);
void dfs2(int, int);
point *check(point *&);
void update(point *, int, int, int = 1, int = n);
int query(point *, int, int, int = 1, int = n);
int lca(int, int);
int main() {
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 1; i <= m; ++i) {
        check(root[i]);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &col[i]);
    }
    for (int i = 1; i < n; ++i) {
        scanf("%d %d", &x, &y);
        addedge(x, y);
    }
    dfs1(1, 1);
    dfs2(1, 1);
    for (int i = 1; i <= n; ++i) {
        update(root[col[i]], dfn[i], 1);
    }
    for (int i = 1; i <= q; ++i) {
        scanf("%d %d %d", &x, &y, &z);
        t = lca(x, y);
        if (t == x || t == y) {
            printf("%d\n", t);
            continue;
        }
        x = t;
        while (x != 1 && !query(root[z], dfn[up[x]], dfn[x])) {
            x = fa[up[x]];
        }
        l = dfn[up[x]];
        r = dfn[x];
        while (l < r) {
            mid = (l + r) >> 1;
            if (query(root[z], l, mid)) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        printf("%d\n", udf[l]);
    }
    return 0;
}
inline void insert(int x, int y) {
    ++ccnt;
    next[ccnt] = head[x];
    head[x] = ccnt;
    to[ccnt] = y;
}
inline void addedge(int x, int y) {
    insert(x, y);
    insert(y, x);
}
inline void dfs1(int v, int f) {
    fa[v] = f;
    size[v] = 1;
    deep[v] = deep[fa[v]] + 1;
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
inline void dfs2(int v, int p) {
    up[v] = p;
    dfn[v] = ++CLOCK;
    udf[CLOCK] = v;
    if (son[v]) {
        dfs2(son[v], up[v]);
    }
    for (int u = head[v]; u; u = next[u]) {
        if (to[u] == fa[v] || to[u] == son[v]) {
            continue;
        }
        dfs2(to[u], to[u]);
    }
}
inline point *check(point *&v) { return v ? v : v = ++cnt; }
inline void update(point *v, int x, int y, int l, int r) {
    if (l == r) {
        v->data += y;
        return;
    }
    int mid = (l + r) >> 1;
    if (x <= mid) {
        update(check(v->lson), x, y, l, mid);
    } else {
        update(check(v->rson), x, y, mid + 1, r);
    }
    v->data = (v->lson ? v->lson->data : 0) +
        (v->rson ? v->rson->data : 0);
    // l == r ? (void)(v->data += y) : ((x <= mid ?
    //     update(check(v->lson), x, y, l, mid) :
    //     update(check(v->rson), x, y, mid + 1, r)),
    //     (void)(v->data = (v->lson ? v->lson->data : 0) +
    //     (v->rson ? v->rson->data : 0)));
}
inline int query(point *v, int x, int y, int l, int r) {
    if (x <= l && r <= y) {
        return v->data;
    }
    int mid = (l + r) >> 1, tmp = 0;
    if (x <= mid && v->lson) {
        tmp += query(v->lson, x, y, l, mid);
    }
    if (y > mid && v->rson) {
        tmp += query(v->rson, x, y, mid + 1, r);
    }
    return tmp;
    // return x <= l && r <= y ? v->data : (x <= mid && v->lson ?
    //     query(v->lson, x, y, l, mid) : 0) + (y > mid &&
    //     v->rson ? query(v->rson, x, y, mid + 1, r) : 0);
}
inline int lca(int x, int y) {
    while (up[x] != up[y]) {
        if (deep[up[x]] < deep[up[y]]) {
            std::swap(x, y);
        }
        x = fa[up[x]];
    }
    return deep[x] < deep[y] ? x : y;
}
