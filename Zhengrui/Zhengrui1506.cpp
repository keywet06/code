#include <bits/stdc++.h>
const int N = 10005;
const int M = 200005;
const int inf = 0x3fffffff;
int S, T, cnt, m, n, x, y, z;
int next[M], to[M], liu[M];
int head[N], vis[N], dis[N], sta[N];
void addtwoedge(int, int, int);
void addoneedge(int, int, int);
void insert(int, int, int);
long long Dinic();
int SPFA();
long long dfs(int = S, int = inf);
int main() {
    scanf("%d %d %d %d", &n, &m, &S, &T);
    while (m--) {
        scanf("%d %d %d", &x, &y, &z);
        addoneedge(x, y, z);
    }
    printf("%lld\n", Dinic());
    return 0;
}
inline void addoneedge(int x, int y, int z) {
    insert(x, y, z);
    insert(y, x, 0);
}
inline void insert(int x, int y, int z) {
    ++cnt;
    next[cnt] = head[x];
    head[x] = cnt;
    to[cnt] = y;
    liu[cnt] = z;
}
inline long long Dinic() {
    long long tmp = 0;
    while (SPFA()) {
        tmp += dfs();
    }
    return tmp;
}
inline int SPFA() {
    memset(dis, 127, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    std::queue<int> queue;
    queue.push(S);
    dis[S] = 0;
    sta[S] = 1;
    while (!queue.empty()) {
        int v = queue.front();
        queue.pop();
        sta[v] = 0;
        for (int u = head[v]; u; u = next[u]) {
            if (liu[u] && dis[v] + 1 < dis[to[u]]) {
                dis[to[u]] = dis[v] + 1;
                if (!sta[to[u]]) {
                    queue.push(to[u]);
                    sta[to[u]] = 1;
                }
            }
        }
    }
    return dis[T] != dis[0];
}
inline long long dfs(int v, int low) {
    if (v == T) {
        return low;
    }
    int res = 0;
    for (int u = head[v]; u; u = next[u]) {
        if (liu[u] && dis[v] + 1 == dis[to[u]]) {
            int tmp = dfs(to[u], std::min(low, liu[u]));
            res += tmp;
            low -= tmp;
            liu[u] -= tmp;
            liu[((u + 1) ^ 1) - 1] += tmp;
            if (!low) {
                break;
            }
        }
    }
    if (!res) {
        dis[v] = 0;
    }
    return res;
}