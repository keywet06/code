#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
const int K = 25;
const int M = 600005;
const int N = 300005;
int size[K][N], size2[K][N];
long long cnt, n, k, x, y, z;
long long to[M], next[M], val[M];
long long head[N], fa[N], vf[N];
long long ans[K][N], ans2[K][N];
void insert(long long, long long, long long);
void addedge(long long, long long, long long);
void dfs(long long, long long);
void dfs2(long long, int &);
int main() {
    register int l, v, u, i;
    scanf("%lld %lld", &n, &k);
    for (i = 1; i < n; ++i) {
        scanf("%lld %lld %lld", &x, &y, &z);
        addedge(x, y, z);
    }
    dfs(1, 1);
    for (l = 2; l <= k; ++l) {
        for (v = 1; v <= n; ++v) {
            for (u = head[v]; u; u = next[u]) {
                if (to[u] == fa[v]) {
                    continue;
                }
                ans[l][v] += ans[l - 1][to[u]] + size[l - 1][to[u]] * val[u];
            }
        }
    }
    for (v = 1; v <= n; ++v) {
        ans2[1][v] = ans[1][v] + vf[v];
        size2[0][v] = 1;
    }
    for (l = 2; l <= k; ++l) {
        ans2[l][1] = ans[l][1];
        size2[l][1] = size[l][1];
        for (u = head[1]; u; u = next[u]) {
            dfs2(to[u], l);
        }
    }
    printf("%lld", ans2[k][1]);
    for (i = 2; i <= n; ++i) {
        printf(" %lld", ans2[k][i]);
    }
    printf("\n");
    return 0;
}
inline void insert(long long x, long long y, long long z) {
    ++cnt;
    next[cnt] = head[x];
    head[x] = cnt;
    to[cnt] = y;
    val[cnt] = z;
}
inline void addedge(long long x, long long y, long long z) {
    insert(x, y, z);
    insert(y, x, z);
}
inline void dfs(long long v, long long f) {
    fa[v] = f;
    for (int i = 0; i <= k; ++i) {
        size[i][v] = 1;
    }
    size2[1][v] = 1;
    register int i;
    for (int u = head[v]; u; u = next[u]) {
        ++size2[1][v];
        if (to[u] == fa[v]) {
            vf[v] = val[u];
            continue;
        }
        dfs(to[u], v);
        for (int i = 1; i <= k; ++i) {
            size[i][v] += size[i - 1][to[u]];
        }
        ans[1][v] += val[u];
    }
}
inline void dfs2(long long v, int &l) {
    size2[l][v] = size[l][v] + size2[l - 1][fa[v]] - size[l - 2][v];
    ans2[l][v] = ans[l][v] + ans2[l - 1][fa[v]] - ans[l - 2][v] + (size2[l - 1][fa[v]] - size[l - 2][v] - size[l - 2][v]) * vf[v];
    for (int u = head[v]; u; u = next[u]) {
        if (to[u] == fa[v]) {
            continue;
        }
        dfs2(to[u], l);
    }
}