#include <bits/stdc++.h>
const int N = 2000000;
double cost[N], dis[N];
int cnt, n, m;
int xx[N], yy[N], head[N], to[N], next[N], flag[N], now[N];
std::queue<int> que;
void addedge(int, int, double);
void insert(int, int, double);
double SPFA();
double co(int);
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d", &xx[i], &yy[i]);
    }
    for (int i = 1; i <= n; ++i) {
        addedge(1, i + 1, yy[i]);
        addedge(i + 1, n + 2, m - yy[i]);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            addedge(i + 1, j + 1, sqrt((xx[i] - xx[j]) * (xx[i] - xx[j]) + (yy[i] - yy[j]) * (yy[i] - yy[j])));
        }
    }
    printf("%.2f\n", SPFA());
    return 0;
}
inline void addedge(int x, int y, double cos) {
    insert(x, y, cos);
    insert(y, x, cos);
}
inline void insert(int x, int y, double cos) {
    ++cnt;
    next[cnt] = head[x];
    head[x] = cnt;
    cost[cnt] = cos;
    to[cnt] = y;
    now[cnt] = x;
}
inline double SPFA() {
    memset(dis, 127, sizeof(dis));
    que.push(1);
    dis[1] = 0;
    flag[1] = 1;
    while(!que.empty()) {
        int v = que.front();
        que.pop();
        flag[v] = 0;
        for (int u = head[v]; u; u = next[u]) {
            if (std::max(dis[v], co(u)) < dis[to[u]]) {
                if (!flag[to[u]]) {
                    que.push(to[u]);
                    flag[to[u]] = 1;
                }
                dis[to[u]] = std::max(dis[v], co(u));
            }
        }
    }
    return dis[n + 2];
}
inline double co(int u) {
    if (now[u] == 1 || now[u] == n + 2 || to[u] == 1 || to[u] == n + 2) {
        return cost[u];
    }
    return cost[u] / 2;
}