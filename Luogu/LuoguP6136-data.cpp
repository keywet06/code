#include <bits/stdc++.h>
const int N = 110005;
char ch;
int root, tp, n, opt, x, cnt, u, t, f, last, ans;
int val[N], num[N], size[N], fa[N];
int son[N][2];
void printtree();
inline int read() {
    tp = 0;
    do {
        ch = getchar();
    } while (ch < '0' || ch > '9');
    do {
        tp = (tp << 3) + (tp << 1) + ch - '0';
        ch = getchar();
    } while ('0' <= ch && ch <= '9');
    return tp;
}
inline void pushup(int u) {
    size[u] = size[son[u][0]] + size[son[u][1]] + num[u];
}
inline int get(int u) { return son[fa[u]][1] == u; }
inline void rotate(int u) {
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
    while (fa[u]) {
        if (fa[fa[u]] && get(u) == get(fa[u])) {
            rotate(fa[u]);
        }
        rotate(u);
    }
}
inline void insert(int x) {
    if (!root) {
        val[root = cnt = 1] = x;
        num[1] = size[1] = 1;
        return;
    }
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
    u = root;
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
    printtree();
    find(x);
    if (num[root] > 1) {
        --num[root];
        --size[root];
    } else if (!son[root][0] || !son[root][1]) {
        root = son[root][0] + son[root][1];
        makeempty(fa[root]);
        fa[root] = 0;
    } else if (son[son[root][0]][1]) {
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
inline void rank(int x) {
    u = root;
    while (1) {
        if (x <= size[son[u][0]]) {
            u = son[u][0];
        } else {
            x -= size[son[u][0]] + num[u];
            if (x <= 0) {
                splay(u);
                return;
            }
            u = son[u][1];
        }
    }
}
inline void lowerbound(int x) {
    insert(x);
    int u = son[root][0];
    while (son[u][1]) u = son[u][1];
    del(x);
    splay(u);
}
inline void upperbound(int x) {
    insert(x);
    int u = son[root][1];
    while (son[u][0]) u = son[u][0];
    del(x);
    splay(u);
}
inline void printtree() {
    return;
    system("\"C:\\Program Files\\Git\\bin\\bash\" 36m.tmp");
    for (int i = 1; i <= cnt; ++i) {
        if (!num[i]) {
            continue;
        }
        fprintf(stderr, "Debug: node[%d] = {\n", i);
        fprintf(stderr, "Debug:     val: %d,\n", val[i]);
        fprintf(stderr, "Debug:     fa: %d,\n", fa[i]);
        fprintf(stderr, "Debug:     son: [%d, %d],\n", son[i][0], son[i][1]);
        fprintf(stderr, "Debug:     num: %d,\n", num[i]);
        fprintf(stderr, "Debug:     size: %d\n", size[i]);
        fprintf(stderr, "Debug: };\n");
    }
    system("\"C:\\Program Files\\Git\\bin\\bash\" 0m.tmp");
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
        num[cnt] = 1;
        val[cnt] = val[i];
    }
    for (int i = cnt + 1; i <= x; ++i) val[i] = 0;
    son[cnt][1] = 0;
    for (int i = 1; i <= n; ++i) {
        printtree();
        opt = read();
        x = read() ^ last;
        if (opt == 1) {
            insert(x);
        } else if (opt == 2) {
            del(x);
        } else if (opt == 3) {
            insert(x);
            find(x);
            ans ^= last = size[son[root][0]] + 1;
            del(x);
        } else if (opt == 4) {
            rank(x);
            ans ^= last = val[root];
        } else if (opt == 5) {
            lowerbound(x);
            ans ^= last = val[root];
        } else {
            upperbound(x);
            ans ^= last = val[root];
        }
    }
    printf("%d\n", ans);
    return 0;
}