#include <bits/stdc++.h>
const int N = 1005;
double eist[N];
double dist[N][N];
int a, b, c, d, n, u;
int x[N], y[N];
int main() {
    scanf("%d %d %d %d %d %d",&n, &a, &b, &c, &d, &u);
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d", &x[i], &y[i]);
    }
    memset(eist, 127, sizeof(eist));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            dist[i][j] = dist[j][i] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
            eist[i] = std::min(eist[i], dist[i][j]);
            eist[j] = std::min(eist[j], dist[j][i]);
        }
    }
    
    return 0;
}