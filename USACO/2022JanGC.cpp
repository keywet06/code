#include <bits/stdc++.h>

using int64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    // int n;
    // std::cin >> n;
    // int64 k = 1ll * n + 1;
    // std::vector<std::vector<std::pair<int, int64> > > To(n + 1);
    // for (int i = 1, x; i <= n; ++i) {
    //     std::cin >> x;
    //     To[i].emplace_back(x, k);
    //     if (x + 1 <= n) To[x + 1].emplace_back(i, -k - 1);
    // }
    // for (int i = 1; i < n; ++i) To[i + 1].emplace_back(i, 0);
    // std::vector<int64> Dis(n + 1, 9e17);
    // std::vector<int> Vis(n + 1);
    // std::queue<int> Que;
    // int S = n;
    // Dis[S] = 4e17, Que.push(S), Vis[S] = 1;
    // while (!Que.empty()) {
    //     auto u = Que.front();
    //     Que.pop(), Vis[u] = 0;
    //     for (auto [v, d] : To[u]) {
    //         if (Dis[u] + d < Dis[v]) {
    //             Dis[v] = Dis[u] + d;
    //             if (!Vis[v]) Que.push(v), Vis[v] = 1;
    //         }
    //     }
    // }
    // std::cout << k << '\n';
    // for (int i = 1; i <= n; ++i) std::cout << Dis[i] - Dis[1] << '\n';
    int n;
    std::cin >> n;
    int64 k = n + 1;
    std::vector<int> f(n + 1), d(n + 1), r(n + 1);
    for (int i = 1; i <= n; ++i) std::cin >> f[i], ++d[f[i]];
    std::vector<int64> a(n + 2);
    for (int i = 1; i <= n; ++i) {
        a[f[i] + 1] = a[i] + k + 1, ++r[f[i] + 1];
        for (int j = f[i]; j > 1 && a[j] > a[j + 1] ||
                           (r[j] == 1 && a[j] < a[j + 1] - 1 || r[j] == 0);
             --j) {
            a[j] = a[j + 1] - 1, r[j] = 2;
        }
        // for (int i = 1; i <= n; ++i) std::cout << a[i] << ' ';
        // std::cout << '\n';
    }
    std::cout << k << '\n';
    for (int i = 1; i <= n; ++i) std::cout << a[i] << '\n';
    return 0;
}