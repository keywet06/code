#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#define ll long long
#define N 40003
using namespace std;

struct edge {
    int v, w;
    edge(int v = 0, int w = 0) : v(v), w(w) {}
};

vector<edge> g[N], adj[N];
int dfn[N], low[N], fa[N];
int top[N], son[N], size[N], dep[N], b[N], sum[N], dis[N];
int n, m, q, cnt, ext;

inline void read(int &x);
void print(int x);
void tarjan(int u, int f);
inline int min(int x, int y);
inline void solve(int u, int v, int w);
void dfs1(int u, int f);
void dfs2(int u, int f);
inline int lca(int u, int v);
inline int find(int u, int f);

signed main() {
    int u, v, p, w, A, B, ans;
    read(n), read(m), read(q);
    ext = n;
    for (int i = 1; i <= m; ++i) {
        read(u), read(v), read(w);
        g[u].push_back(edge(v, w));
        g[v].push_back(edge(u, w));
    }
    tarjan(1, 0);
    dfs1(1, 0);
    dfs2(1, 1);
    while (q--) {
        read(u), read(v);
        p = lca(u, v);
        if (p <= n)
            ans = dis[u] + dis[v] - (dis[p] << 1);
        else {
            A = find(u, p), B = find(v, p);
            ans = dis[u] + dis[v] - dis[A] - dis[B];
            if (sum[A] < sum[B]) swap(A, B);
            ans += min(sum[A] - sum[B], sum[p] + sum[B] - sum[A]);
        }
        print(ans);
        putchar('\n');
    }
    return 0;
}

inline int find(int u, int f) {
    int res;
    while (top[u] != top[f]) {
        res = top[u];
        u = fa[top[u]];
    }
    return u == f ? res : son[f];
}

inline int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

void dfs1(int u, int f) {
    fa[u] = f;
    dep[u] = dep[f] + 1;
    size[u] = 1;
    int v, t = -1, l = adj[u].size();
    for (int i = 0; i < l; ++i) {
        v = adj[u][i].v;
        if (v == f) continue;
        dis[v] = dis[u] + adj[u][i].w;
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > t) {
            t = size[v];
            son[u] = v;
        }
    }
}

void dfs2(int u, int f) {
    top[u] = f;
    if (son[u] == 0) return;
    dfs2(son[u], f);
    int v, l = adj[u].size();
    for (int i = 0; i < l; ++i) {
        v = adj[u][i].v;
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

void tarjan(int u, int f) {
    dfn[u] = low[u] = ++cnt;
    int v, w, l = g[u].size();
    for (int i = 0; i < l; ++i) {
        v = g[u][i].v;
        if (v == f) continue;
        w = g[u][i].w;
        if (!dfn[v]) {
            fa[v] = u, b[v] = w;
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
        } else
            low[u] = min(low[u], dfn[v]);
        if (low[v] <= dfn[u]) continue;

        adj[u].push_back(edge(v, w));
        adj[v].push_back(edge(u, w));
    }
    for (int i = 0; i < l; ++i) {
        v = g[u][i].v;
        if (fa[v] == u || dfn[v] <= dfn[u]) continue;

        solve(u, v, g[u][i].w);
    }
}

inline void solve(int u, int v, int w) {
    ++ext;
    int pw, pre = w, i = v;
    while (i != fa[u]) {
        sum[i] = pre;
        pre += b[i];
        i = fa[i];
    }
    sum[ext] = sum[u];
    sum[u] = 0;
    i = v;
    while (i != fa[u]) {
        pw = min(sum[i], sum[ext] - sum[i]);

        adj[ext].push_back(edge(i, pw));
        adj[i].push_back(edge(ext, pw));
        i = fa[i];
    }
}

inline int min(int x, int y) { return x < y ? x : y; }

inline void read(int &x) {
    x = 0;
    char c = getchar();
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = getchar();
    }
}

void print(int x) {
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}