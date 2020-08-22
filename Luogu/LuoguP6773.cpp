#include <bits/stdc++.h>
const int N = 100;
int n, m, x, y;
int fa[N];
std::vector<int> ed[N];
std::vector<int> to[N];
inline void dfs(int u, int f) {
    fa[u] = f;
    for (int i = 0; i < to[u].size(); ++i) {
        if (to[u][i] == f) continue;
        dfs(to[u][i], u);
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
    std::cin >> m;
    for (int i = 1; i <= m; ++i) {
        std::cin >> x >> y;
        for (int u = y; u != x; u = fa[u]) {
            ed[i].push_back(u);
        }
    }
    long long ans = 0;
    for (int i = 1; i < (1 << (n - 1)); ++i) {
        int flag = 1;
        for (int j = 1; j <= m; ++j) {
            int s = 1;
            for (int e = 0; e < ed[j].size(); ++e) {
                if (1 << (ed[j][e] - 2) & i) s = 0;
            }
            if (s) {
                flag = 0;
                break;
            }
        }
        ans += flag;
    }
    std::cout << ans << std::endl;
    return 0;
}