#include <bits/stdc++.h>
const int N = 2000005;
int cnt, n, x, y;
int next[N], to[N], head[N], from[N], subt[N], nmax[N];
void insert(int, int);
void addedge(int, int);
void dfs1(int, int);
void dfs2(int, int, int);
int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        scanf("%d %d", &x, &y);
        addedge(x, y);
    }
    dfs1(1, 1);
    dfs2(1, 1, 0);
    for (int i = 1; i <= n; ++i) {
        printf("%d\n", std::max(from[i], subt[i]));
    }
    return 0;
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
inline void dfs1(int v, int fa) {
    for (int u = head[v]; u; u = next[u]) {
        if (to[u] == fa) {
            continue;
        }
        dfs1(to[u], v);
        if (subt[to[u]] >= subt[v]) {
            nmax[v] = subt[v];
            subt[v] = subt[to[u]] + 1;
        } else if (subt[to[u]] >= nmax[v]) {
            nmax[v] = subt[to[u]] + 1;
        }
    }
}
inline void dfs2(int v, int fa, int fr) {
    from[v] = fr;
    for (int u = head[v]; u; u = next[u]) {
        if (to[u] == fa) {
            continue;
        }
        dfs2(to[u], v, std::max(subt[v] == subt[to[u]] + 1 ? nmax[v] : subt[v], from[v]) + 1);
    }
}