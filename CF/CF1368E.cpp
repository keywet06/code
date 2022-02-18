#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int T;
    std::cin >> T;
    while (T--) {
        int n, m;
        std::cin >> n >> m;
        std::vector<int> Deg(n), Vis(n);
        std::vector<std::vector<int> > To(n);
        for (int i = 0, u, v; i < m; ++i) {
            std::cin >> u >> v, --u, --v;
            To[u].push_back(v), ++Deg[v];
        }
        std::vector<int> A, B, C;
        for (int i = 0; i < n; ++i) {
            if (Deg[i]) continue;
            A.push_back(i);
            for (int v : To[i]) Vis[v] = 1;
        }
        for (int i = 0; i < n; ++i) {
            if (Vis[i] != 1) continue;
            B.push_back(i);
            for (int v : To[i]) Vis[v] = 2;
        }
        for (int i = 0; i < n; ++i) {
            if (Vis[i] == 2) C.push_back(i + 1);
        }
        std::cout << C.size() << std::endl;
        for (int x : C) std::cout << x << ' ';
        std::cout << std::endl;
    }
    return 0;
}