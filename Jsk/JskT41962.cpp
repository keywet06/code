#include <bits/stdc++.h>
const int N = 2000005;
int cnt, m, n, k, x, y, z, l, r, mid;
int coffe[N], next[N], to[N], head[N], cost[N], vis[N], dis[N];
std::queue<int> queue;
void insert(int, int, int);
void addedge(int, int, int);
int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= k; ++i) {
        scanf("%d", &x);
        coffe[x] = 1;
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d %d", &x, &y, &z);
        addedge(x, y, z);
        r = std::max(r, z);
    }
    memset(dis, 127, sizeof(dis));
    dis[1] = 0;
    vis[1] = 1;
    queue.push(1);
    while (!queue.empty()) {
        int v = queue.front();
        queue.pop();
        vis[v] = 0;
        for (int u = head[v]; u; u = next[u]) {
            if (dis[v] + cost[u] < dis[to[u]]) {
                dis[to[u]] = dis[v] + cost[u];
                if (!vis[to[u]]) {
                    vis[to[u]] = 1;
                    queue.push(to[u]);
                }
            }
        }
    }
    memset(vis, 0, sizeof(vis));
    queue.push(1);
    vis[1] = 1;
    while (!queue.empty()) {
        int v = queue.front();
        queue.pop();
        for (int u = head[v]; u; u = next[u]) {
            if (dis[v] + cost[u] == dis[to[u]] && !vis[to[u]] &&
                !coffe[to[u]]) {
                vis[to[u]] = 1;
                queue.push(to[u]);
            }
        }
    }
    if (!vis[n]) {
        printf("0\n");
        return 0;
    }
    l = 1;
    while (l < r) {
        mid = (l + r + 1) >> 1;
        memset(vis, 0, sizeof(vis));
        queue.push(1);
        vis[1] = 1;
        while (!queue.empty()) {
            int v = queue.front();
            queue.pop();
            for (int u = head[v]; u; u = next[u]) {
                if (dis[v] + cost[u] == dis[to[u]] && !vis[to[u]] &&
                    cost[u] >= mid && !coffe[to[u]]) {
                    vis[to[u]] = 1;
                    queue.push(to[u]);
                }
            }
        }
        if (vis[n]) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    printf("%d\n", l);
    return 0;
}
inline void insert(int x, int y, int z) {
    ++cnt;
    next[cnt] = head[x];
    head[x] = cnt;
    to[cnt] = y;
    cost[cnt] = z;
}
inline void addedge(int x, int y, int z) {
    insert(x, y, z);
    insert(y, x, z);
}