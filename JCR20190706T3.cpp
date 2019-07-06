#include <bits/stdc++.h>
const int M = 2005;
const int N = 1005;
int S, T, Q, cnt, m, n, x, y, z;
int next[M], to[M], cost[M];
int head[N], vis[N];
long long dis[N];
void addedge(int, int, int);
void insert(int, int, int);
long long dijstra();
int main() {
    scanf("%d %d", &n, &m, &S, &T);
    while (m--) {
        scanf("%d %d %d", &x, &y, &z);
        addedge(x, y, z);
    }
    scanf("%d", &Q);
    while (Q--) {
        scanf("%d", &x);
        printf("%lld\n", dijstra());
    }
    return 0;
}
inline void addedge(int x, int y, int z) {
    insert(x, y, z);
    insert(y, x, z);
}
inline void insert(int x, int y, int z) {
    ++cnt;
    next[cnt] = head[x];
    head[x] = cnt;
    to[cnt] = y;
    cost[cnt] = z;
}
inline long long dijstra() {
    memset(dis, 127, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[S] = 0;
    vis[S] = 1;
    vis[x] = 1;
    for (int u = head[S]; u; u = next[u]) {
        if (!vis[to[u]]) {
            dis[to[u]] = cost[u];
            vis[to[u]] =1;
        }
    }
    for (int i = 2; i < n; ++i) {
        y = 0;
        for (int i = 1; i <= n; ++i) {
            if (!vis[i] && dis[i] < dis[y]) {
                y = i;
            }
        }
        if (!y) {
            return -1;
        }
        vis[y] = 1;
        for (int u = head[y]; u; u = next[u]) {
            
        }
    }
}