#include <bits/stdc++.h>
const int N = 500000;
int cnt, m, n, s, x, y, z, q;
int dis[N], sd[N], to[N], next[N], cost[N], head[N], flag[N];
std::queue<int> que;
int main() {
    scanf("%d %d %d", &n, &s, &m);
    for (int i = 1; i <= s; ++i) {
        scanf("%d", &sd[i]);
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d %d", &x, &y, &z);
        ++cnt;
        to[cnt] = y;
        next[cnt] = head[x];
        cost[cnt] = z;
        head[x] = cnt;
        ++cnt;
        to[cnt] = x;
        next[cnt] = head[y];
        cost[cnt] = z;
        head[y] = cnt;
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i) {
        scanf("%d %d %d", &y, &z, &x);
        que.push(y);
        memset(flag, 0, sizeof(flag));
        memset(dis, 127, sizeof(dis));
        dis[y] = 0;
        flag[y] = 1;
        while (!que.empty()) {
            int v = que.front();
            que.pop();
            flag[v] = 0;
            for (int u = head[v]; u; u = next[u]) {
                if (dis[v] + cost[u] <= x && dis[v] + cost[u] < dis[to[u]]) {
                    if (to[u] == z) {
                        printf("TAK\n");
                        flag[0] = 1;
                        break;
                    }
                    if (!flag[to[u]]) {
                        que.push(to[u]);
                        flag[to[u]] = 1;
                    }
                    if (sd[to[u]] == 1) {
                        dis[to[u]] = 0;
                    } else {
                        dis[to[u]] = dis[v] + cost[u];
                    }
                }
            }
            if (flag[0]) {
                break;
            }
        }
        if (!flag[0]) {
            printf("NIE\n");
        }
    }
    return 0;
}