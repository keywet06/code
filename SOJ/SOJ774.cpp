#include <bits/stdc++.h>
const int N = 100;
int n, x, y, ans;
int fa[N], deep[N], vis[N], a[N];
int as[N][N];
std::vector<int> to[N];
inline void dfs(int u, int f) {
    deep[u] = deep[f] + 1;
    fa[u] = f;
    for (auto v : to[u]) {
        if (v == f) {
            return;
        }
        dfs(v, u);
    }
}
inline void ds(int c) {
    if (c == n + 1) return void(++ans);
    for (int i = 1; i <= n; ++i) {
        if (!vis[i] && (c == 1 || as[a[c - 2]][a[c - 1]] <= as[a[c - 1]][i])) {
            a[c] = i;
            vis[i] = 1;
            ds(c + 1);
            vis[i] = 0;
        }
    }
}
int main() {
    std::cin >> n;
    for (int i = 1; i < n; ++i) {
        std::cin >> x >> y;
        to[x].push_back(y);
        to[y].push_back(x);
    }
    dfs(1, 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            x = i, y = j;
            if (deep[x] < deep[y]) std::swap(x, y);
            while (deep[x] > deep[y]) x = fa[x];
            while (x != y) x = fa[x], y = fa[y];
            as[i][j] = deep[x];
        }
    }
    ds(1);
    std::cout << ans << std::endl;
    return 0;
}