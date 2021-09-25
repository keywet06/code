#include <bits/stdc++.h>

#define pub push_back

const int C = 3;
const int N = 2000005;

int n, x, y, ans;
int dp[N][C];

std::vector<int> to[N];

inline int &mid(int &x, int y) { return x = std::min(x, y); }

inline void dfs(int u, int fa, int deep) {
    int a = 0, b = 0;
    for (int v : to[u]) {
        if (v == fa) continue;
        dfs(v, u, deep + 1);
        a += dp[v][0], b += dp[v][1];
    }
    mid(dp[u][2], a + 1);
    mid(dp[u][0], b);
    for (int v : to[u]) {
        if (v == fa) continue;
        mid(dp[u][1], b - dp[v][1] + dp[v][2]);
    }
    mid(dp[u][0], mid(dp[u][1], dp[u][2]));
    if (deep == 2) ans += dp[u][0];
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i < n; ++i) {
        std::cin >> x >> y;
        to[x].pub(y), to[y].pub(x);
    }
    memset(dp, 15, sizeof(dp));
    dfs(1, 1, 0);
    std::cout << ans << std::endl;
    return 0;
}