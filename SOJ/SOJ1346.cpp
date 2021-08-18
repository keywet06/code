#include <bits/stdc++.h>

using int64 = long long;

const int N = 150005;

int n, c, x, y;
int vis[N];

int64 ans;
int64 a[N];

std::vector<int> to[N];

inline void dfs(int u, int d, int64 s) {
    ans = std::max(ans, s += d * a[u]), vis[u] = c;
    for (int v : to[u]) {
        if (vis[v] == c) continue;
        dfs(v, d + 1, s);
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i < n; ++i) {
        std::cin >> x >> y;
        to[x].push_back(y);
        to[y].push_back(x);
    }
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    for (c = 1; c <= n; ++c) dfs(c, 1, 0);
    std::cout << ans << std::endl;
    return 0;
}