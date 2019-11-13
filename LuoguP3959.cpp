#include <bits/stdc++.h>
const int M = 1005;
const int N = 15;
const int INF = 100000000;
int n, m, ans, x, y, z;
int dp[M];
int dis[N];
int edge[N][N];
void dfs(int x) {
    int tmp;
    for (int i = 1; i <= n; ++i) {
        if (!((1 << (i - 1)) & x)) {
            continue;
        }
        for (int j = 1; j <= n; ++j) {
            if (((1 << (j - 1)) & x) == 0 && edge[i][j] != INF &&
                dp[x | (1 << (j - 1))] > dp[x] + dis[i] * edge[i][j]) {
                tmp = dis[j];
                dis[j] = dis[i] + 1;
                dp[x | (1 << (j - 1))] = dp[x] + dis[i] * edge[i][j];
                dfs(x | (1 << (j - 1)));
                dis[j] = tmp;
            }
        }
    }
}
int main() {
    scanf("%d %d", &n, &m);
    memset(edge, 127, sizeof(edge));
    ans = **edge;
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d %d", &x, &y, &z);
        edge[x][y] = std::min(edge[x][y], z);
        edge[y][x] = std::min(edge[y][x], z);
    }
    for (int T = 1; T <= n; ++T) {
        memset(dis, 127, sizeof(dis));
        memset(dp, 127, sizeof(dp));
        dis[T] = 1;
        dp[1 << (T - 1)] = 0;
        dfs(1 << (T - 1));
        ans = std::min(ans, dp[(1 << n) - 1]);
    }
    printf("%d\n", ans);
    return 0;
}