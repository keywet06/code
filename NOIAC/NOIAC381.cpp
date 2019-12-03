#include <bits/stdc++.h>
const int C = 26;
const int N = 200005;
const int mod1 = 1e9 + 7;
const int mod2 = 1e9 + 9;
class pair {
    public:
        int len;
        long long a, b;
        pair();
};
char str[N];
int CLOCK, cnt, m, n, x, y, z, w;
int deep[N], dfn[N], fa[N], head[N], left[N], next[N], right[N], size[N], son[N], to[N], udfn[N], up[N];
long long h1sh1[N], h1sh2[N], h2sh1[N], h2sh2[N], z1[N], z2[N];
int operator == (pair, pair);
pair makepair(long long, long long, int);
void insert(int, int);
void addedge(int, int);
void dfs1(int, int);
void dfs2(int, int);
int len(int);
void updata(int);
void build(int, int, int);
pair mergea(pair, pair);
pair mergeb(pair, pair);
pair querya(int, int, int);
pair queryb(int, int, int);
int queryS(int, int, int, int);
int main() {
    scanf("%d %d", &n, &m);
    scanf("%s", str + 1);
    z1[0] = z2[0] = 1;
    for (int i = 1; i <= n; ++i) {
        str[i] -= 'a';
        z1[i] = (z1[i - 1] * C) % mod1;
        z2[i] = (z2[i - 1] * C) % mod2;
    }
    for (int i = 1; i < n; ++i) {
        scanf("%d %d", &x, &y);
        addedge(x, y);
    }
    dfs1(1, 1);
    dfs2(1, 1);
    build(1, 1, n);
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d %d %d", &x, &y, &z, &w);
        printf("%s\n", queryS(x, y, z, w) ? "Yes" : "No");
    }
    return 0;
}
inline pair::pair() {
    this->a = this->b = this->len = 0;
}
inline int operator == (pair x, pair y) {
    return x.a == y.a && x.b == y.b && x.len == y.len;
}
inline pair makepair(long long a, long long b, int len) {
    pair p;
    p.a = a;
    p.b = b;
    p.len = len;
    return p;
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
    size[v] = 1;
    fa[v] = f;
    deep[v] = deep[f] + 1;
    for (int u = head[v]; u; u = next[u]) {
        if (to[u] == f) {
            continue;
        }
        dfs1(to[u], v);
        size[v] += size[to[u]];
        if (size[to[u]] > size[son[v]]) {
            son[v] = to[u];
        }
    }
}
inline void dfs2(int v, int top) {
    dfn[v] = ++CLOCK;
    udfn[CLOCK] = v;
    up[v] = top;
    if (son[v]) {
        dfs2(son[v], top);
    }
    for (int u = head[v]; u; u = next[u]) {
        if (to[u] == fa[v] || to[u] == son[v]) {
            continue;
        }
        dfs2(to[u], to[u]);
    }
}
inline int len(int v) {
    return right[v] - left[v] + 1;
}
inline void updata(int v) {
    h1sh1[v] = (h1sh1[v << 1] + h1sh1[v << 1 | 1] * z1[len(v << 1)]) % mod1;
    h1sh2[v] = (h1sh2[v << 1] + h1sh2[v << 1 | 1] * z2[len(v << 1)]) % mod2;
    h2sh1[v] = (h2sh1[v << 1] * z1[len(v << 1 | 1)] + h2sh1[v << 1 | 1]) % mod1;
    h2sh2[v] = (h2sh2[v << 1] * z2[len(v << 1 | 1)] + h2sh2[v << 1 | 1]) % mod2;
}
inline void build(int v, int l, int r) {
    left[v] = l;
    right[v] = r;
    if (l == r) {
        h1sh1[v] = h1sh2[v] = h2sh1[v] = h2sh2[v] = str[udfn[l]];
        return;
    }
    int mid = (left[v] + right[v]) >> 1;
    build(v << 1, l, mid);
    build(v << 1 | 1, mid + 1, r);
    updata(v);
}
inline pair mergea(pair a, pair b) {
    return makepair((a.a + b.a * z1[a.len]) % mod1, (a.b + b.b * z2[a.len]) % mod2, a.len + b.len);
}
inline pair mergeb(pair a, pair b) {
    return makepair((a.a * z1[b.len] + b.a) % mod1, (a.b * z2[b.len] + b.b) % mod2, a.len + b.len);
}
inline pair querya(int v, int x, int y) {
    pair a;
    if (x <= left[v] && right[v] <= y) {
        a = makepair(h1sh1[v], h1sh2[v], len(v));
    } else {
        int mid = (left[v] + right[v]) >> 1;
        if (x > mid) {
            a = querya(v << 1 | 1, x, y);
        } else if (y <= mid) {
            a = querya(v << 1, x, y);
        } else {
            a = mergea(querya(v << 1, x, y), querya(v << 1 | 1, x, y));
        }
    }
    return a;
}
inline pair queryb(int v, int x, int y) {
    pair a;
    if (x <= left[v] && right[v] <= y) {
        a = makepair(h2sh1[v], h2sh2[v], len(v));
    } else {
        int mid = (left[v] + right[v]) >> 1;
        if (x > mid) {
            a = queryb(v << 1 | 1, x, y);
        } else if (y <= mid) {
            a = queryb(v << 1, x, y);
        } else {
            a = mergea(queryb(v << 1, x, y), queryb(v << 1 | 1, x, y));
        }
    }
    return a;
}
inline int queryS(int ax, int ay, int bx, int by) {
    pair px, py, qx, qy;
    while (up[ax] != up[ay]) {
        if (deep[ax] > deep[ay]) {
            px = mergeb(px, queryb(1, dfn[up[ax]], dfn[ax]));
            ax = fa[up[ax]];
        } else {
            py = mergea(py, querya(1, dfn[up[ay]], dfn[ay]));
            ay = fa[up[ay]];
        }
    }
    if (deep[ax] > deep[ay]) {
        px = mergeb(px, queryb(1, dfn[ay], dfn[ax]));
    } else {
        py = mergea(py, querya(1, dfn[ax], dfn[ay]));
    }
    px = mergeb(px, py);
    while (up[bx] != up[by]) {
        if (deep[bx] > deep[by]) {
            qx = mergeb(qx, queryb(1, dfn[up[bx]], dfn[bx]));
            bx = fa[up[bx]];
        } else {
            qy = mergea(qy, querya(1, dfn[up[by]], dfn[by]));
            by = fa[up[by]];
        }
    }
    if (deep[bx] > deep[by]) {
        qx = mergeb(qx, queryb(1, dfn[by], dfn[bx]));
    } else {
        qy = mergea(qy, querya(1, dfn[bx], dfn[by]));
    }
    qx = mergeb(qx, qy);
    return px == qx;
}