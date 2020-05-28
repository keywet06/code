#include <bits/stdc++.h>
const int N = 110005;
int root, n, opt, x, cnt;
int val[N], num[N], size[N], fa[N];
int son[N][2];
inline int read() {
    extern int x, ch;
    x = 0;
    do {
        ch = getchar();
    } while (ch < '0' || ch > '9');
    do {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    } while ('0' <= ch && ch <= '9');
    return x;
}
inline void pushup(int u) {
    size[u] = size[son[u][0]] + size[son[u][1]] + num[u];
}
inline int get(int u) { return son[fa[u]][1] == u; }
inline void rotate(int u) {
    extern int t;
    t = get(u);
    if (son[fa[u]][t] = son[u][!t]) fa[son[u][!t]] = fa[u];
    son[u][!t] = fa[u];
    if (fa[u] = fa[fa[u]]) son[fa[u]][get(son[u][!t])] = u;
    fa[son[u][!t]] = u;
    if (!fa[u]) root = u;
    pushup(son[u][!t]);
    pushup(u);
}
inline void splay(int u) {
    while (u != root) {
        if (fa[u] != root && get(u) != get(fa[u])) {
            rotate(fa[u]);
        } else {
            rotate(fa[u]);
            rotate(u);
        }
    }
}
inline void insert(int x) {
    if (!root) {
        val[root = cnt = 1] = x;
        num[1] = size[1] = 1;
        return;
    }
    extern int u, f;
    f = root;
    while (f) {
        if (x == val[u = f]) {
            ++num[u];
            splay(u);
            return;
        }
        f = son[u][x > val[u]];
    }
    son[u][x > val[u]] = ++cnt;
    fa[cnt] = u;
    val[cnt] = x;
    num[cnt] = size[cnt] = 1;
    splay(cnt);
}
inline void find(int x) {
    extern int u;
    u = 1;
    while (1) {
        if (x == val[u]) {
            splay(u);
            return;
        }
        u = son[u][x > val[u]];
    }
}
inline void makeempty(int u) {
    val[u] = fa[u] = son[u][0] = son[u][1] = size[u] = num[u] = 0;
}
inline void del(int x) {
    if (size[root] == 1) {
        makeempty(root);
        root = 0;
        return;
    }
    find(x);
    if (num[root] > 1) {
        --num[root];
        --size[root];
    } else if (!son[root][0] || !son[root][1]) {
        root = son[root][0] + son[root][1];
        makeempty(fa[root]);
        fa[root] = 0;
    } else if (son[son[root][0]][1]) {
        extern int u;
        u = son[son[root][0]][1];
        while (son[u][1]) u = son[u][1];
        u = fa[u];
        fa[son[u][1]] = 0;
        son[son[u][1]][0] = son[root][0];
        son[son[u][1]][1] = son[root][1];
        makeempty(root);
        root = son[u][1];
        fa[son[root][0]] = root;
        fa[son[root][1]] = root;
        son[u][1] = 0;
        splay(u);
    } else {
        son[son[root][0]][1] = son[root][1];
        fa[son[root][1]] = son[son[root][0]][1];
        root = son[root][0];
        makeempty(fa[root]);
        fa[root] = 0;
    }
}
int main() {
    x = read();
    n = read();
    for (int i = 1; i <= x; ++i) val[i] = read();
    std::sort(val + 1, val + x + 1);
    root = 1;
    for (int i = 1; i <= x; ++i) {
        if (i > 1 && val[i] == val[i - 1]) {
            ++num[cnt];
            continue;
        }
        size[++cnt] = x - i + 1;
        son[cnt][1] = cnt + 1;
        fa[cnt] = cnt - 1;
    }
    son[cnt][1] = 0;
    for (int i = 1; i <= n; ++i) {
        opt = read();
        x = read();
        if (opt == 1) {
            insert(x);
        } else if (opt == 2) {
            del(x);
        } else if (opt == 3) {
        } else if (opt == 4) {
        } else if (opt == 5) {
        } else {
        }
    }
    return 0;
}