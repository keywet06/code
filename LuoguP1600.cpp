#include "kw/Tu.hpp"
const int N = 1000005;
const int M = 30000005;
class point {
    public:
        point *lson, *rson;
        int data;
};
point po[M];
point *cnt = po;
point *gheadup[N], *gheaddown[N];
int m, n, tmp, x, y, z;
int ans[N], tim[N], deep[N], upval[N], downval[N], size[N], hson[N], up[N], f[N];
kw::Tu<N, N, int> tu;
void update(point*, int, int, int = 1, int = n << 1);
int query(point*, int, int = 1, int = n << 1);
void merge(point*, point*, int = 1, int = n << 1);
void dfs1(int, int);
void dfs2(int, int);
void dfs3(int);
int lca(int, int);
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i < n; ++i) {
        scanf("%d %d", &x, &y);
        tu.insert(x, y, 1);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &tim[i]);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    for (int i = 1; i <= n; ++i) {
        gheadup[i] = ++cnt;
        gheaddown[i] = ++cnt;
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d", &x, &y);
        tmp = lca(x, y);
        z = deep[x];
        update(gheadup[x], z, 1);
        if (f[tmp]) {
            update(gheadup[f[tmp]], z, -1);
        }
        z = (deep[tmp] << 1) - deep[x] + n;
        update(gheaddown[y], z, 1);
        update(gheaddown[tmp], z, -1);
    }
    dfs3(1);
    for (int i = 1; i <= n; ++i) {
        printf("%d ", ans[i]);
    }
    return 0;
}
inline void update(point *v, int x, int y, int l, int r) {
    if (l == r) {
        v->data += y;
        return;
    }
    int mid = (l + r) >> 1;
    if (x <= mid) {
        if (!v->lson) {
            v->lson = ++cnt;
        }
        update(v->lson, x, y, l, mid);
    }
    if (x > mid) {
        if (!v->rson) {
            v->rson = ++cnt;
        }
        update(v->rson, x, y, mid + 1, r);
    }
}
inline int query(point *v, int x, int l, int r) {
    if (l == r) {
        return v->data;
    }
    int mid = (l + r) >> 1;
    if (x <= mid && v->lson) {
        return query(v->lson, x, l, mid);
    }
    if (x > mid && v->rson) {
        return query(v->rson, x, mid + 1, r);
    }
    return 0;
}
inline void merge(point *v1, point *v2, int l, int r) {
    if (l == r) {
        v1->data += v2->data;
        return;
    }
    int mid = (l + r) >> 1;
    if (v1->lson && v2->lson) {
        merge(v1->lson, v2->lson, l, mid);
    } else if (v2->lson) {
        v1->lson = v2->lson;
    }
    if (v1->rson && v2->rson) {
        merge(v1->rson, v2->rson, mid + 1, r);
    } else if (v2->rson) {
        v1->rson = v2->rson;
    }
}
inline void dfs1(int v, int fa) {
    f[v] = fa;
    deep[v] = deep[f[v]] + 1;
    upval[v] = deep[v] + tim[v];
    downval[v] = deep[v] - tim[v] + n;
    size[v] = 1;
    for (kw::Tu<N, N, int>::iterator u = tu.GetHead(v); u; u = u->next) {
        if (u->to == fa) {
            continue;
        }
        dfs1(u->to, v);
        size[v] += size[u->to];
        if (size[u->to] > size[hson[v]]) {
            hson[v] = u->to;
        }
    }
}
inline void dfs2(int v, int uper) {
    up[v] = uper;
    if (hson[v]) {
        dfs2(hson[v], uper);
    }
    for (kw::Tu<N, N, int>::iterator u = tu.GetHead(v); u; u = u->next) {
        if (u->to == f[v] || u->to == hson[v]) {
            continue;
        }
        dfs2(u->to, u->to);
    }
}
inline void dfs3(int v) {
    for (kw::Tu<N, N, int>::iterator u = tu.GetHead(v); u; u = u->next) {
        if (u->to == f[v]) {
            continue;
        }
        dfs3(u->to);
        merge(gheadup[v], gheadup[u->to]);
        merge(gheaddown[v], gheaddown[u->to]);
    }
    ans[v] = query(gheadup[v], upval[v]) + query(gheaddown[v], downval[v]);
}
inline int lca(int x, int y) {
    while (up[x] != up[y]) {
        if (deep[up[x]] < deep[up[y]]) {
            std::swap(x, y);
        }
        x = f[up[x]];
    }
    return deep[x] < deep[y] ? x : y;
}