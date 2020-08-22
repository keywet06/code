#include <bits/stdc++.h>
const int N = 10005;
const int M = 200005;
const long long INF = 1000000016000000063;
int S, T, n, m, x, y, z, cnt = 1, sum;
int head[N], dis[N], vis[N], gap[N], cur[N];
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
    queue.push(T);
    dis[T] = 0;
    vis[T] = 1;
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop();
        vis[u] = 0;
        for (int e = head[u]; e; e = next[e]) {
            if (flow[e ^ 1] && dis[u] + 1 < dis[to[e]]) {
                ++gap[dis[to[e]] = dis[u] + 1];
                if (!vis[to[e]]) {
                    queue.push(to[e]);
                    vis[to[e]] = 1;
                }
            }
        }
    }
    return dis[S] != dis[0];
}
inline long long dfs(int u, long long limit) {
    if (u == T) return limit;
    long long rlow = 0, used = 0;
    for (int &e = cur[u]; e; e = next[e]) {
        if (!flow[e] || dis[to[e]] != dis[u] - 1) continue;
        if (!(rlow = dfs(to[e], std::min(limit - used, flow[e])))) continue;
        used += rlow;
        flow[e] -= rlow;
        flow[e ^ 1] += rlow;
        if (used == limit) return used;
    }
    if (!--gap[dis[u]]) dis[S] = n + 1;
    ++gap[++dis[u]];
    return used;
}
inline long long ISAP() {
    long long ans = 0;
    SPFA();
    while (dis[S] < n) {
        memcpy(cur, head, sizeof(head));
        ans += dfs(S, INF);
    }
    return ans;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m;
    S = n * m + 1, T = n * m + 2;
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= m; ++j) {
            std::cin >> x;
            ++y;
            sum += x;
            if (i + j & 1) {
                addedge(S, y, x);
            } else {
                addedge(y, T, x);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            x = i * m + j, y = i * m + j + 1;
            if (!(i + j & 1)) std::swap(x, y);
            addedge(x, y, INT_MAX);
        }
    }
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 1; j <= m; ++j) {
            x = i * m + j, y = (i + 1) * m + j;
            if (!(i + j & 1)) std::swap(x, y);
            addedge(x, y, INT_MAX);
        }
    }
    n = T;
    std::cout << sum - ISAP() << std::endl;
    return 0;
}