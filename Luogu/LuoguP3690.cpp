#include <bits/stdc++.h>
const int B = 2;
const int N = 100005;
int n, m, opt, x, y;
int val[N], xsum[N], fa[N], tag[N];
int son[N][B];
inline int get(int u) {
    return son[fa[u]][0] == u ? 0 : (son[fa[u]][1] == u ? 1 : -1);
}
inline int isroot(int u) { return get(u) == -1; }
inline int isRoot(int u) { return !fa[u]; }
inline void pushup(int u) {
    xsum[u] = xsum[son[u][0]] ^ xsum[son[u][1]] ^ val[u];
}
inline void pushr(int u) {
    std::swap(son[u][0], son[u][1]);
    tag[u] ^= 1;
}
inline void pushdown(int u) {
    if (tag[u]) {
        tag[u] = 0;
        pushr(son[u][0]);
        pushr(son[u][1]);
    }
}
inline void rotate(int u) {
    pushdown(fa[u]);
    pushdown(u);
    int t = get(u);
    if (son[fa[u]][t] = son[u][!t]) {
        fa[son[fa[u]][t]] = fa[u];
    }
    son[u][!t] = fa[u];
    if (!isroot(fa[u] = fa[fa[u]])) {
        son[fa[u]][get(son[u][!t])] = u;
    }
    fa[son[u][!t]] = u;
    pushup(son[u][!t]);
    pushup(u);
}
inline void splay(int u) {
    while (!isroot(u)) {
        if (isroot(fa[u])) {
            rotate(u);
        } else if (get(u) == get(fa[u])) {
            rotate(fa[u]);
            rotate(u);
        } else {
            rotate(u);
            rotate(u);
        }
    }
}
inline void access(int u) {
    for (int v = 0; u; v = u, u = fa[u]) {
        splay(u);
        son[u][1] = v;
        pushup(u);
    }
}
inline void makeroot(int u) {
    access(u);
    splay(u);
    pushr(u);
}
inline int findroot(int u) {
    access(u);
    splay(u);
    while (son[u][0]) {
        pushdown(u);
        u = son[u][0];
    }
    splay(u);
    return u;
}
inline void split(int u, int v) {
    makeroot(u);
    access(v);
    splay(v);
}
inline void link(int u, int v) {
    makeroot(u);
    if (findroot(v) != u) {
        fa[u] = v;
    }
}
inline void cut(int u, int v) {
    makeroot(u);
    if (findroot(v) != u || fa[v] != u || son[v][0]) {
        return;
    }
    fa[v] = son[u][1] = 0;
    pushup(u);
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        std::cin >> val[i];
        xsum[i] = val[i];
    }
    for (int i = 1; i <= m; ++i) {
        std::cin >> opt >> x >> y;
        if (opt == 0) {
            split(x, y);
            std::cout << xsum[y] << std::endl;
        } else if (opt == 1) {
            link(x, y);
        } else if (opt == 2) {
            cut(x, y);
        } else {
            splay(y);
            val[x] = y;
            pushup(x);
        }
    }
    return 0;
}