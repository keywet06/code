#include <bits/stdc++.h>
const int N = 505;
const int M = 10005;
int S, T, n, m, x, y, z, cnt = 1;
int head[N], dis[N], vis[N];
int next[M], to[M];
long long flow[M];
inline void insert(int x, int y, int z) {
    next[++cnt] = head[x];
    head[x] = cnt;
    to[cnt] = y;
    flow[cnt] = z;
}
inline void addedge(int x, int y, int z) {
    insert(x, y, z);
    insert(y, x, 0);
}
inline int SPFA() {
    memset(dis, 127, sizeof(dis));
    std::queue<int> queue;
    queue.push(S);
    dis[S] = 0;
    vis[S] = 1;
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop();
        vis[u] = 0;
        for (int e = head[u]; e; e = next[e]) {
            if (flow[e] && dis[u] + 1 < dis[to[e]]) {
                dis[to[e]] = dis[u] + 1;
                if (!vis[to[e]]) {
                    queue.push(to[e]);
                    vis[to[e]] = 1;
                }
            }
        }
    }
    return dis[T] != dis[0];
}
inline long long dfs(int u, long long limit) {
    if (u == T) return limit;
    long long rlow = 0, used = 0;
    for (int e = head[u]; e; e = next[e]) {
        if (!flow[e] || dis[to[e]] != dis[u] + 1) continue;
        if (!(rlow = dfs(to[e], std::min(limit - used, flow[e])))) continue;
        used += rlow;
        flow[e] -= rlow;
        flow[e ^ 1] += rlow;
        if (used == limit) break;
    }
    if (!used) dis[u] = 0;
    return used;
}
inline long long Dinic() {
    long long ans = 0;
    while (SPFA()) {
        ans += dfs(S, 4611686018427387903);
    }
    return ans;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m >> S >> T;
    for (int i = 1; i <= m; ++i) {
        std::cin >> x >> y >> z;
        addedge(x, y, z);
    }
    std::cout << Dinic() << std::endl;
    return 0;
}