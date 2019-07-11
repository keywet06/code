#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 100000 + 10;
vector<int> g[N];
int CLOCK, n;
int par[N], son[N], sz[N], dep[N], top[N], dfn[N], who[N];
int sum[N << 2], lz[N << 2];
void pre(int, int);
void dfs(int, int);
void pushdown(int, int, int);
void update(int, int, int, int, int, int);
int query(int, int, int, int, int);
void pathC(int, int, int);
int pathS(int, int);
int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int q;
    scanf("%d", &q);
    pre(1, 1);
    dfs(1, 1);
    while (q--) {
        char op[2];
        int u, v, x;
        scanf("%s %d %d", op, &u, &v);
        if (op[0] == 'C') {
            scanf("%d", &x);
            pathC(u, v, x);
        } else {
            printf("%d\n", pathS(u, v));
        }
    }
}
inline void pre(int u, int p) {
	par[u] = p,
    son[u] = 0,
    sz[u] = 1,
    dep[u] = dep[p] + 1;
    int mx = 0;
    for (int i = 0; i < g[u].size(); ++i) {
        int v = g[u][i];
        if (p == v) {
            continue;
        }
        pre(v, u);
        sz[u] += sz[v];
        if (sz[v] > mx) {
            mx = sz[v],
        	son[u] = v;
        }
    }
}
inline void dfs(int u, int p) {
    top[u] = p,
    dfn[u] = ++CLOCK;
    if (son[u]) {
        dfs(son[u], p);
    }
    for (int i = 0; i < g[u].size(); ++i) {
        int v = g[u][i];
        if (v == son[u] || v == par[u]) {
            continue;
        }
        dfs(v, v);
    }
}
inline void pushdown(int rt, int l, int r) {
    if (lz[rt]) {
        int mid = (l + r) >> 1;
        lz[rt << 1] += lz[rt];
        sum[rt << 1] += (mid - l + 1) * lz[rt];
        lz[rt << 1 | 1] += lz[rt];
        sum[rt << 1 | 1] += (r - mid) * lz[rt];
        lz[rt] = 0;
    }
}
inline void update(int l, int r, int rt, int L, int R, int x) {
    if (L <= l && r <= R) {
        lz[rt] += x;
        sum[rt] += (r - l + 1) * x;
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(rt, l ,r);
    if (L <= mid) {
        update(l, mid, rt << 1, L, R, x);
    }
    if (R > mid) {
        update(mid + 1, r, rt << 1 | 1, L, R, x);
    }
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}
inline int query(int l, int r, int rt, int L, int R) {
    if (L <= l && r <= R) {
        return sum[rt];
    }
    int mid = (l + r) >> 1, ans = 0;
    pushdown(rt, l, r);
    if (L <= mid) {
        ans += query(l, mid, rt << 1, L, R);
    }
    if (R > mid) {
        ans += query(mid + 1, r, rt << 1 | 1, L, R);
    }
    return ans;
}
inline void pathC(int u, int v, int x) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) {
            swap(u, v);
        }
        update(1, n, 1, dfn[top[u]], dfn[u], x);
        u = par[top[u]];
    }
    if (dep[u] > dep[v]) {
        swap(u, v);
    }
    update(1, n, 1, dfn[u], dfn[v], x);
}
inline int pathS(int u, int v) {
    int ans = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) {
            swap(u, v);
        }
        ans += query(1, n, 1, dfn[top[u]], dfn[u]);
        u = par[top[u]];
    }
    if (dep[u] > dep[v]) {
        swap(u, v);
    }
    ans += query(1, n, 1, dfn[u], dfn[v]);
    return ans;
}