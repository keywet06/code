#include <bits/stdc++.h>
const int N = 1000005;
const int LOG_N = 20;
int cnt, tmp, log_n, n, m, s;
int logs[LOG_N];
int head[N], dfn[N], next[N], to[N], deep[N];
int father[N][LOG_N];
int read();
void addedge(int, int);
void insert(int, int);
void get_tree(int);
int lca(int, int);
int lowbit(int);
int main() {
    scanf("%d %d %d", &n, &m, &s);
    log_n = 0;
    tmp = 1;
    while (tmp < n) {
        logs[tmp] = log_n;
        ++log_n;
        tmp <<= 1;
    }
    for (int i = 1; i < n; ++i) {
        addedge(read(), read());
    }
    get_tree(s);
    father[s][0] = s;
    for (int i = 1; i <= n; ++i) {
        if (i == s) {
            continue;
        }
        for (int j = 1; j <= log_n; ++j) {
            father[i][j] = father[father[i][j - 1]][j - 1];
        }
    }
    while (m--) {
        printf("%d\n", lca(read(), read()));
    }
    return 0;
}
inline int read() {
    int x = 0, ch = getchar(), f = 1;
    while (ch < '0' || '9' < ch) {
        f = ((ch != '-') << 1) - 1;
        ch = getchar();
    }
    x = ch - '0';
    ch = getchar();
    while ('0' <= ch && ch <= '9') {
        x = (ch ^ '0') + (x << 3) + (x << 1);
        ch = getchar();
    }
    ungetc(ch, stdin);
    return x * f;
}
inline void addedge(int x, int y) {
    insert(x, y);
    insert(y, x);
}
inline void insert(int x, int y) {
    ++cnt;
    next[cnt] = head[x];
    head[x] = cnt;
    to[cnt] = y;
}
inline void get_tree(int u) {
    dfn[u] = 1;
    for (int v = head[u]; v; v = next[v]) {
        if (!dfn[to[v]]) {
            father[to[v]][0] = u;
            deep[to[v]] = deep[u] + 1;
            get_tree(to[v]);
        }
    }
}
inline int lca(int x, int y) {
    if (deep[x] > deep[y]) {
        std::swap(x, y);
    }
    for (int i = deep[y] - deep[x]; i; i -= lowbit(i)) {
        y = father[y][logs[lowbit(i)]];
    }
    tmp = log_n;
    while (x != y) {
        while (tmp > 0 && father[x][tmp] == father[y][tmp]) {
            --tmp;
        }
        x = father[x][tmp];
        y = father[y][tmp];
        --tmp;
    }
    return x;
}
inline int lowbit(int x) { return x & (-x); }
