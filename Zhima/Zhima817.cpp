#include <bits/stdc++.h>

const int N = 505;

int n, ans, u, min;
int dis[N], use[N];
int a[N][N];

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> dis[i];
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) std::cin >> a[i][j];
    }
    for (int i = 1; i <= n; ++i) {
        min = 1000000000;
        for (int j = 1; j <= n; ++j) {
            if (dis[j] < min && !use[j]) min = dis[j], u = j;
        }
        use[u] = 1, ans += dis[u];
        for (int j = 1; j <= n; ++j) dis[j] = std::min(dis[j], a[u][j]);
    }
    std::cout << ans << std::endl;
    return 0;
}