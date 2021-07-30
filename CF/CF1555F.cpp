#include <bits/stdc++.h>

const int B = 2;
const int N = 800005;

int n, m, o, x, y, z;
int a[N], val[N], fa[N], rev[N], used[N], use[N], pus[N];
int son[N][B];

inline int g(int u) { return son[fa[u]][1] == u; }

inline int isRoot(int u) { return son[fa[u]][0] != u && son[fa[u]][1] != u; }

inline void useu(int u) {
    pus[u] = 1, used[u] |= use[u] = u > n;
}

inline void pushdown(int u) {
    if (rev[u]) {
        rev[u] = 0, std::swap(son[u][0], son[u][1]);
        if (son[u][0]) rev[son[u][0]] ^= 1;
        if (son[u][1]) rev[son[u][1]] ^= 1;
    }
    if (pus[u]) {
        pus[u] = 0;
        if (son[u][0]) useu(son[u][0]);
        if (son[u][1]) useu(son[u][1]);
    }
}

inline void update(int u) {
    val[u] = a[u] ^ val[son[u][0]] ^ val[son[u][1]];
    use[u] = used[u] | use[son[u][0]] | use[son[u][1]];
}

inline void rotate(int u) {
    int t = g(u);
    if (son[fa[u]][t] = son[u][!t]) fa[son[u][!t]] = fa[u];
    son[u][!t] = fa[u], fa[u] = fa[fa[u]];
    if (!isRoot(son[u][!t])) son[fa[u]][g(son[u][!t])] = u;
    fa[son[u][!t]] = u, update(son[u][!t]), update(u);
}

inline void splay(int u) {
    while (!isRoot(u)) {
        pushdown(fa[fa[u]]), pushdown(fa[u]), pushdown(u);
        if (!isRoot(fa[u])) rotate(g(u) == g(fa[u]) ? fa[u] : u);
        rotate(u);
    }
}

inline void access(int u) {
    int p = 0;
    pushdown(u);
    while (u) {
        splay(fa[u]), splay(u), son[u][1] = p, p = u, u = fa[u], update(p);
    }
}

inline void makeroot(int u) { access(u), splay(u), rev[u] ^= 1; }

inline void split(int u, int v) { makeroot(u), access(v), splay(u); }

inline void link(int u, int v) {
    makeroot(u), makeroot(v), pushdown(v);
    int p = u;
    while (pushdown(p), son[p][0]) p = son[p][0];
    if (p != v) fa[u] = v;
}

inline void cut(int u, int v) {
    split(u, v);
    if (fa[v] == u && !son[v][0]) fa[v] = 0, son[u][1] = 0, update(u);
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> m, o = n;
    while (m--) {
        std::cin >> x >> y >> z;
        makeroot(x), makeroot(y), pushdown(y);
        int p = x;
        while (pushdown(p), son[p][0]) p = son[p][0];
        if (x != y) {
            ++o, a[o] = val[o] = z;
            link(x, o), link(y, o);
            std::cout << "YES\n";
            continue;
        }
        split(x, y);
        if (val[x] != 1 || used[x]) {
            std::cout << "NO\n";
            continue;
        }
        pus[x] = 1;
        std::cout << "YES\n";
    }
    // while (m--) {
    //     std::cin >> o >> x >> y;
    //     if (o == 0) {
    //         split(x, y);
    //         std::cout << val[x] << '\n';
    //     } else if (o == 1) {
    //         link(x, y);
    //     } else if (o == 2) {
    //         cut(x, y);
    //     } else {
    //         a[x] = y, update(x), splay(x);
    //     }
    // }
    return 0;
}