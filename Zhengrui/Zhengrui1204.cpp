#include <bits/stdc++.h>
const int N = 100000;
const int Np = N + 5;
int n, m, k, x, y;
int dis[Np], st[Np], last[Np], lock[Np];
std::vector<int> in[Np], out[Np];
void dfs(int u, int dis);
inline void dfs(int u, int d) {
    lock[u] = 1;
    dis[u] = d;
    for (auto &&v: in[u]) {
        if (lock[v] || dis[v] > d) {
            continue;
        }
        if (last[v]) {
            --last[v];
            continue;
        }
        dfs(v, d);
    }
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) {
        std::cin >> dis[i];
        st[i] = i;
        last[i] = k;
    }
    for (int i = 1; i <= m; ++i) {
        std::cin >> x >> y;
        in[y].push_back(x);
    }
    std::sort(st + 1, st + n + 1, [](int x, int y) { return dis[x] > dis[y]; });
    for (int i = 1; i <= n; ++i) {
        if (!lock[st[i]]) {
            dfs(st[i], dis[st[i]]);
        }
    }
    for (int i = 1; i <= n; ++i) {
        std::cout << dis[i] << std::endl;
    }
    return 0;
}