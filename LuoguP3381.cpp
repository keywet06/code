#include <bits/stdc++.h>
const int N = 5005;
const int M = 100005;
const int inf = 0x3fffffff;
int S, T, m, n, w, x, y, z, maxflow, mincost, cnt = 1;
int next[M], to[M], liu[M], cost[M];
int head[N], pre[N], dis[N], sta[N];
void addedge(int, int, int, int);
void insert(int, int, int, int);
void costflow();
int SPFA();
int main() {
    scanf("%d %d %d %d", &n, &m, &S, &T);
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d %d %d", &x, &y, &z, &w);
        addedge(x, y, z, w);
    }
    costflow();
    printf("%lld %lld\n", maxflow, mincost);
    return 0;
}
inline void addedge(int x, int y, int z, int w) {
    insert(x, y, z, w);
    insert(y, x, 0, -w);
}
inline void insert(int x, int y, int z, int w) {
    ++cnt;
    next[cnt] = head[x];
    head[x] = cnt;
    to[cnt] = y;
    liu[cnt] = z;
    cost[cnt] = w;
}
inline void costflow() {
    maxflow = 0;
    mincost = 0;
    while (SPFA()) {
        int tmp = inf;
        for (int u = T; u != S; u = to[pre[u] ^ 1]) {
            tmp = std::min(tmp, liu[pre[u]]);
        }
        maxflow += tmp;
        for (int u = T; u != S; u = to[pre[u] ^ 1]) {
            liu[pre[u]] -= tmp;
            liu[pre[u] ^ 1] += tmp;
            mincost += cost[pre[u]] * tmp;
        }
    }
}
inline int SPFA() {
    memset(dis, 127, sizeof(dis));
    memset(pre, 0, sizeof(pre));
    std::queue<int> queue;
    queue.push(S);
    sta[S] = 1;
    dis[S] = 0;
    while (!queue.empty()) {
        int v = queue.front();
        queue.pop();
        sta[v] = 0;
        for (int u = head[v]; u; u = next[u]) {
            if (liu[u] && dis[v] + cost[u] < dis[to[u]]) {
                if (!sta[to[u]]) {
                    queue.push(to[u]);
                    sta[to[u]] = 1;
                }
                dis[to[u]] = dis[v] + cost[u];
                pre[to[u]] = u;
            }
        }
    }
    return pre[T];
}