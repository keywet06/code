#include <bits/stdc++.h>
const int B = 2;
const int C = 25;
const int N = 200005;
const long long INF = 1e12;
char s[C];
int a, b, cnt, m, n, t, x, y, z;
int head[N], next[N], to[N], cost[N], deep[N];
int fa[N][C];
long long rx0, rx1, ry0, ry1, n0, n1;
long long dp[B][N];
long long val[B][B][N][C];
void insert(int, int);
void addedge(int, int);
void dfs1(int, int);
long long as(int, int, int, int);
void dfs2(int);
int lca(int, int);
int main() {
    scanf("%d %d %s", &n, &m, s);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &cost[i]);
    }
    for (int i = 1; i < n; ++i) {
        scanf("%d %d", &x, &y);
        addedge(x, y);
    }
    dfs1(1, 1);
    memset(val, -1, sizeof(val));
    dfs2(1);
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d %d %d", &x, &a, &y, &b);
        if (deep[x] > deep[y]) {
            std::swap(x, y);
            std::swap(a, b);
        }
        z = lca(x, y);
        if (x == z) {
            if (fa[y][0] == x && !a && !b) {
                printf("-1\n");
                continue;
            }
            rx0 = b ? INF : dp[y][0];
            rx1 = b ? dp[y][1] : INF;
            printf("%lld %lld\n", rx0, rx1);
            t = deep[y] - deep[x] - 1;
            for (int i = 0; t; ++i) {
                if (t & (1 << i)) {
                    n0 = std::min(rx0 + as(0, 0, y, i), rx1 + as(1, 0, y, i));
                    n1 = std::min(rx0 + as(0, 1, y, i), rx1 + as(1, 1, y, i));
                    rx0 = n0;
                    rx1 = n1;
                    t ^= 1 << i;
                    y = fa[y][i];
                }
            }
            printf("%lld %lld\n", rx0, rx1);
            rx0 = a ? INF : n1 + as(1, 0, y, 0);
            rx1 = a ? std::min(n0 + as(0, 1, y, 0), n1 + as(1, 1, y, 0)) : INF;
            t = deep[y = x] - 1;
            for (int i = 0; t; ++i) {
                if (t & (1 << i)) {
                    n0 = std::min(rx0 + as(0, 0, y, i), rx1 + as(1, 0, y, i));
                    n1 = std::min(rx0 + as(0, 1, y, i), rx1 + as(1, 1, y, i));
                    rx0 = n0;
                    rx1 = n1;
                    t ^= 1 << i;
                    y = fa[y][i];
                }
            }
            printf("%lld %lld\n", rx0, rx1);
        } else {
            rx0 = a ? INF : dp[x][0];
            rx1 = a ? dp[x][1] : INF;
            t = deep[x] - deep[z] - 1;
            for (int i = 0; t; ++i) {
                if (t & (1 << i)) {
                    n0 = std::min(rx0 + as(0, 0, x, i), rx1 + as(1, 0, x, i));
                    n1 = std::min(rx0 + as(0, 1, x, i), rx1 + as(1, 1, x, i));
                    rx0 = n0;
                    rx1 = n1;
                    t ^= 1 << i;
                    x = fa[x][i];
                }
            }
            ry0 = a ? INF : dp[y][0];
            ry1 = a ? dp[y][1] : INF;
            t = deep[y] - deep[z] - 1;
            for (int i = 0; t; ++i) {
                if (t & (1 << i)) {
                    n0 = std::min(ry0 + as(0, 0, y, i), ry1 + as(1, 0, y, i));
                    n1 = std::min(ry0 + as(0, 1, y, i), ry1 + as(1, 1, y, i));
                    ry0 = n0;
                    ry1 = n1;
                    t ^= 1 << i;
                    y = fa[y][i];
                }
            }
            n0 = a && b ? dp[z][0] - dp[x][1] - dp[y][1] + rx1 + ry1 : INF;
            n1 = dp[z][1] - std::min(dp[x][0], dp[x][1]) - std::min(dp[y][0],
                dp[y][1]) + (a ? rx1 : rx0) + (b ? ry1 : ry0);
            x = z;
            rx0 = n0;
            rx1 = n1;
            t = deep[x] - 1;
            for (int i = 0; t; ++i) {
                if (t & (1 << i)) {
                    n0 = std::min(rx0 + as(0, 0, x, i), rx1 + as(1, 0, x, i));
                    n1 = std::min(rx0 + as(0, 1, x, i), rx1 + as(1, 1, x, i));
                    rx0 = n0;
                    rx1 = n1;
                    t ^= 1 << i;
                    x = fa[x][i];
                }
            }
        }
        printf("%lld\n", std::min(rx0, rx1));
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
inline void dfs1(int v, int f) {
    deep[v] = deep[f] + 1;
    fa[v][0] = f;
    for (int i = 1; 1 << i <= deep[v]; ++i) {
        fa[v][i] = fa[fa[v][i - 1]][i - 1];
    }
    dp[1][v] += cost[v];
    for (int u = head[v]; u; u = next[u]) {
        if (to[u] == fa[v][0]) {
            continue;
        }
        dfs1(to[u], v);
        dp[0][v] += dp[1][to[u]];
        dp[1][v] += std::min(dp[0][to[u]], dp[1][to[u]]);
    }
}
inline long long as(int a, int b, int c, int d) {
    return ~val[a][b][c][d] ? val[a][b][c][d] : INF;
}
inline void dfs2(int v) {
    if (v != 1) {
        val[0][1][v][0] = dp[1][fa[v][0]] - std::min(dp[0][v], dp[1][v]);
        val[1][0][v][0] = dp[0][fa[v][0]] - dp[1][v];
        val[1][1][v][0] = dp[1][fa[v][0]] - std::min(dp[0][v], dp[1][v]);
    }
    for (int i = 1; 1 << i <= deep[v]; ++i) {
        val[0][0][v][i] = (val[0][0][v][i] = std::min(as(0, 0, v, i - 1) +
            as(0, 0, fa[v][i - 1], i - 1), as(0, 1, v, i - 1) + as(1, 0,
            fa[v][i - 1], i - 1))) < INF ? val[0][0][v][i] : -1;
        val[0][1][v][i] = (val[0][1][v][i] = std::min(as(0, 0, v, i - 1) +
            as(0, 1, fa[v][i - 1], i - 1), as(0, 1, v, i - 1) + as(1, 1,
            fa[v][i - 1], i - 1))) < INF ? val[0][1][v][i] : -1;
        val[1][0][v][i] = (val[1][0][v][i] = std::min(as(1, 0, v, i - 1) +
            as(0, 0, fa[v][i - 1], i - 1), as(1, 1, v, i - 1) + as(1, 0,
            fa[v][i - 1], i - 1))) < INF ? val[1][0][v][i] : -1;
        val[1][1][v][i] = (val[1][1][v][i] = std::min(as(1, 0, v, i - 1) +
            as(0, 1, fa[v][i - 1], i - 1), as(1, 1, v, i - 1) + as(1, 1,
            fa[v][i - 1], i - 1))) < INF ? val[1][1][v][i] : -1;        
    }
    for (int u = head[v]; u; u = next[u]) {
        if (to[u] == fa[v][0]) {
            continue;
        }
        dfs2(to[u]);
    }
}
inline int lca(int x, int y) {
    int t1, t2;
    if (deep[x] < deep[y]) {
        std::swap(x, y);
    }
    t1 = deep[x] - deep[y];
    for (t2 = 0; t1; ++t2) {
        if (t1 & (1 << t2)) {
            x = fa[x][t2];
            t1 ^= 1 << t2;
        }
    }
    if (x == y) {
        return x;
    }
    for (t1 = 0; fa[x][t1] != fa[y][t1]; ++t1);
    for (; fa[x][0] != fa[y][0]; --t1) {
        if (fa[x][t1] != fa[y][t1]) {
            x = fa[x][t1];
            y = fa[y][t1];
        }
    }
    while (x != y) {
        x = fa[x][0];
        y = fa[y][0];
    }
    return x;
}