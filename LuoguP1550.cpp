#include <bits/stdc++.h>
const int N = 500;
int n, min, x, ans, y;
int dis[N], vis[N];
int cost[N][N];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &x);
        cost[n + 1][i];
        cost[i][n + 1];
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            scanf("%d", &x);
            cost[i][j] = cost[j][i] = x;
        }
    }
    x = 1;
    vis[1] = 1;
    memset(dis, 127, sizeof(dis));
    dis[1] = 0;
    for (int i = 1; i <= n; ++i) {
        y = 0;
        for (int j = 1; j <= n + 1; ++j) {
            if (vis[j]) {
                continue;
            }
            dis[j] = std::min(dis[j], dis[x] + cost[x][j]);
            if (dis[j] < dis[y]) {
                y = j;
            }
        }
        ans += dis[x = y];
        vis[x] = 1;
    }
    printf("%d\n", ans);
    return 0;
}
