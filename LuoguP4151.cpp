#include <bits/stdc++.h>
const int M = 200005;
const int N = 50005;
const int C = 62;
int cnt, n, m, x, y;
int next[M], to[M];
int head[N], vis[N];
long long ans, z;
long long jd[C];
long long val[M];
long long dis[N];
void insert(int, int, long long);
void addedge(int, int, long long);
void insertJ(long long);
void dfs(int, long long);
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d %lld", &x, &y, &z);
        addedge(x, y, z);
    }
    dfs(1, 0);
    for (int i = C - 1; ~i; --i) {
        if (!((1ll << i) & ans) && jd[i]) {
            ans ^= jd[i];
        }
    }
    printf("%lld\n", ans);
    return 0;
}
inline void insert(int x, int y, long long z) {
    ++cnt;
    next[cnt] = head[x];
    head[x] = cnt;
    to[cnt] = y;
    val[cnt] = z;
}
inline void addedge(int x, int y, long long z) {
    insert(x, y, z);
    insert(y, x, z);
}
inline void insertJ(long long n) {
    x = C - 1;
    while (n) {
        for (; ~x; --x) {
            if (n & (1ll << x)) {
                break;
            }
        }
        if (!jd[x]) {
            jd[x] = n;
            break;
        } else {
            n ^= jd[x];
        }
    }
}
inline void dfs(int v, long long now) {
    dis[v] = now;
    vis[v] = 1;
    if (v == n) {
        ans = now;
    }
    for (int u = head[v]; u; u = next[u]) {
        if (vis[to[u]]) {
            insertJ(dis[to[u]] ^ now ^ val[u]);
        } else {
            dfs(to[u], now ^ val[u]);
        }
    }
}