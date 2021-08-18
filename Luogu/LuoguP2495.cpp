#include <bits/stdc++.h>

using int64 = long long;

const int INF = 1000000000;
const int64 INFI = 1000000000000000000;
const int C = 20;
const int N = 250005;
const int M = N << 1;

int cnt, n, x, y, z, q, k, top;
int dfn[N], head[N], deep[N], tr[N], vis[N], dp[N], st[N], rtr[N];
int next[M], to[M], wei[M];
int fa[N][C], val[N][C];

inline void insert(int u, int v, int w) {
    next[++cnt] = head[u];
    head[u] = cnt;
    to[cnt] = v;
    wei[cnt] = w;
}
inline void addedge(int u, int v, int w) { insert(u, v, w), insert(v, u, w); }

inline void dfs(int u) {
    for (int i = 1; i < C; ++i) {
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
        val[u][i] = std::min(val[u][i - 1], val[fa[u][i - 1]][i - 1]);
    }
    dfn[u] = ++cnt;
    for (int e = head[u]; e; e = next[e]) {
        if (dfn[to[e]]) continue;
        fa[to[e]][0] = u, val[to[e]][0] = wei[e], deep[to[e]] = deep[u] + 1;
        dfs(to[e]);
    }
}

inline int vald(int u, int d) {
    int ret = INF;
    for (int i = 0; i < C; ++i) {
        if (d & (1 << i)) {
            ret = std::min(ret, val[u][i]);
            u = fa[u][i];
        }
    }
    return ret;
}
inline int valp(int u, int v) { return vald(u, deep[u] - deep[v]); }

inline int lca(int u, int v) {
    if (deep[u] < deep[v]) std::swap(u, v);
    int d = deep[u] - deep[v];
    for (int i = 0; i < C; ++i) {
        if (d & (1 << i)) u = fa[u][i];
    }
    for (int i = C - 1; ~i; --i) {
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i], v = fa[v][i];
        }
    }
    return u == v ? u : fa[u][0];
}

inline void trick(int u, int c) {
    if (vis[u] < c) vis[u] = c, head[u] = dp[u] = 0;
}

inline void insertx(int u, int v, int c) {
    trick(u, c), trick(v, c);
    insert(u, v, valp(v, u));
}

inline int64 solve(int u, int c) {
    int64 ret = 0;
    for (int e = head[u]; e; e = next[e]) {
        ret += std::min(solve(to[e], c), int64(wei[e]));
    }
    return rtr[u] == c ? INFI : ret;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i < n; ++i) {
        std::cin >> x >> y >> z;
        addedge(x, y, z);
    }
    dfs(fa[1][0] = 1);
    std::cin >> q;
    for (int c = 1; c <= q; ++c) {
        std::cin >> k;
        for (int i = 1; i <= k; ++i) std::cin >> tr[i], rtr[tr[i]] = c;
        std::sort(tr + 1, tr + k + 1,
                  [](int x, int y) { return dfn[x] < dfn[y]; });
        cnt = 0;
        st[++top] = 1, st[++top] = tr[1];
        for (int i = 2; i <= k; ++i) {
            x = lca(tr[i - 1], tr[i]);
            while (dfn[st[top]] > dfn[x]) {
                if (dfn[st[--top]] >= dfn[x]) insertx(st[top], st[top + 1], c);
            }
            if (st[top] != x) insertx(x, st[top + 1], c), st[++top] = x;
            st[++top] = tr[i];
        }
        while (--top) insertx(st[top], st[top + 1], c);
        std::cout << solve(1, c) << '\n';
    }
    return 0;
}