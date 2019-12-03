#include <bits/stdc++.h>
const int C = 4;
const int N = 505;
const int tox[C] = {-1, 0, 0, 1};
const int toy[C] = {0, -1, 1, 0};
int ans, n, m, now, ti, max;
int tobe[N];
int high[N][N], vis[N][N], left[N][N], right[N][N];
void dfs1(int, int);
void dfs2(int, int);
int cmp(int, int);
int main() {
    scanf("%d %d", &n, &m);
    memset(high, 127, sizeof(high));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &high[i][j]);
        }
    }
    for (int i = 1; i <= m; ++i) {
        if (!vis[1][i]) {
            dfs1(1, i);
        }
    }
    for (int i = 1; i <= m; ++i) {
        ans += !vis[n][i];
    }
    if (ans) {
        printf("0\n%d\n", ans);
        return 0;
    }
    memset(vis, 0, sizeof(vis));
    printf("1\n");
    for (int i = 1; i <= m; ++i) {
        vis[n + 1][i] = 1;
        high[n + 1][i] = 0;
        left[n + 1][i] = i;
        right[n + 1][i] = i;
        tobe[i] = i;
    }
    for (int i = 1; i <= m; ++i) {
        if (!vis[1][i]) {
            dfs2(1, i);
        }
    }
    std::sort(tobe + 1, tobe + m + 1, cmp);
    now = 0;
    ti = 0;
    while (now < m) {
        max = 0;
        while (ti < m && left[1][tobe[ti + 1]] <= now + 1) {
            ++ti;
            max = std::max(max, right[1][tobe[ti]]);
        }
        now = max;
        ++ans;
    }
    printf("%d\n", ans);
    return 0;
}
inline void dfs1(int x, int y) {
    vis[x][y] = 1;
    for (int i = 0; i < C; ++i) {
        if (!vis[x + tox[i]][y + toy[i]] &&
            high[x][y] > high[x + tox[i]][y + toy[i]]) {
            dfs1(x + tox[i], y + toy[i]);
        }
    }
}
inline void dfs2(int x, int y) {
    vis[x][y] = 1;
    left[x][y] = m + 1;
    right[x][y] = 0;
    for (int i = 0; i < C; ++i) {
        if (high[x][y] <= high[x + tox[i]][y + toy[i]]) {
            continue;
        }
        if (!vis[x + tox[i]][y + toy[i]]) {
            dfs2(x + tox[i], y + toy[i]);
        }
        left[x][y] = std::min(left[x][y], left[x + tox[i]][y + toy[i]]);
        right[x][y] = std::max(right[x][y], right[x + tox[i]][y + toy[i]]);
    }
}
inline int cmp(int x, int y) {
    return left[1][x] < left[1][y];
}