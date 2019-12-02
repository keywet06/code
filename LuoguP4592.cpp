#include <bits/stdc++.h>
const int C = 30000005;
const int M = 200005;
const int N = 100005;
class Node {
   public:
    int size;
    int son[2];
};
int n, m, cnt, x, y, z, v1, v2;
int next[M], to[M];
int tree[N], head[N], val[N], udf[N], dfn[N], t[N], deep[N], size[N], up[N],
  fa[N], son[N], edf[N];
Node nd[C];
void insert(int, int);
void addedge(int, int);
void ita(int *, int);
void dfs1(int, int);
void dfs2(int, int);
int query(int, int, int);
int queryS(int, int, int);
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
inline void ita(int *a, int x) {
    for (int i = 29; ~i; --i) {
        a[i] = x % 2;
        x /= 2;
    }
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
    dfn[v] = ++cnt;
    udf[cnt] = v;
    if (son[v]) {
        dfs2(son[v], up[v]);
    }
    for (int u = head[v]; u; u = next[u]) {
        if (to[u] == fa[v] || to[u] == son[v]) {
            continue;
        }
        dfs2(to[u], to[u]);
    }
    edf[v] = cnt;
}
inline int query(int v1, int v2, int x) {
    int ans = 0;
    std::swap(v1, v2);
    v1 = tree[v1];
    v2 = tree[v2 - 1];
    ita(t, x);
    for (int j = 0; j < 30; ++j) {
        if (nd[nd[v1].son[t[j] ^ 1]].size - nd[nd[v2].son[t[j] ^ 1]].size) {
            ans = ans << 1 | 1;
            v1 = nd[v1].son[t[j] ^ 1];
            v2 = nd[v2].son[t[j] ^ 1];
        } else {
            ans = ans << 1;
            v1 = nd[v1].son[t[j]];
            v2 = nd[v2].son[t[j]];
        }
    }
    return ans;
}
inline int queryS(int x, int y, int z) {
    int ans = 0;
    while (up[x] != up[y]) {
        if (deep[up[x]] < deep[up[y]]) {
            std::swap(x, y);
        }
        ans = std::max(ans, query(dfn[up[x]], dfn[x], z));
        x = fa[up[x]];
    }
    if (deep[x] > deep[y]) {
        std::swap(x, y);
    }
    return std::max(ans, query(dfn[x], dfn[y], z));
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        std::cin >> val[i];
    }
    for (int i = 1; i < n; ++i) {
        std::cin >> x >> y;
        addedge(x, y);
    }
    cnt = 0;
    dfs1(1, 1);
    dfs2(1, 1);
    tree[0] = cnt = 1;
    for (int i = 1; i <= n; ++i) {
        nd[tree[i] = ++cnt] = nd[tree[i - 1]];
        ita(t, val[udf[i]]);
        ++nd[tree[i]].size;
        for (int v = tree[i], j = 0; j < 30; ++j) {
            nd[++cnt] = nd[nd[v].son[t[j]]];
            v = nd[v].son[t[j]] = cnt;
            ++nd[v].size;
        }
    }
    for (int i = 1; i <= m; ++i) {
        std::cin >> x;
        if (x == 1) {
            std::cin >> x >> y;
            std::cout << query(dfn[x], edf[x], y) << std::endl;
        } else {
            std::cin >> x >> y >> z;
            std::cout << queryS(x, y, z) << std::endl;
        }
    }
    return 0;
}