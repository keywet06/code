#include <bits/stdc++.h>
const int M = 10005;
const int N = 1005;
int m, n, sum, x, y;
int dis[N], head[N];
int next[M], to[M];
void addedge(int, int);
void dfs(int);
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d", &x, &y);
        addedge(x, y);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = head[i]; ~j; j = next[j]) {
            to[j ^ 1] = to[j];
        }
        memset(dis, 0, sizeof(dis));
        sum = 0;
        for (int j = 1; j <= n; ++j) {
            if (i == j) {
                continue;
            }
            if (!dis[j]) {
                ++sum;
                dfs(j);
            }
        }
    }
    return 0;
}