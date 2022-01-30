#include <bits/stdc++.h>

struct Edge {
    int o, u, v, w, id;
    Edge(int O, int U, int V, int W, int Id) : o(O), u(U), v(V), w(W), id(Id) {}
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int n, m, q;
    std::cin >> n >> m >> q;
    std::vector<Edge> Ed;
    int u, v, w;
    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v >> w;
        Ed.emplace_back(0, --u, --v, w, 0);
    }
    for (int i = 0; i < q; ++i) {
        std::cin >> u >> v >> w;
        Ed.emplace_back(1, --u, --v, w, i);
    }
    std::sort(Ed.begin(), Ed.end(), [](Edge x, Edge y) { return x.w < y.w; });
    std::vector<int> f(n);
    for (int i = 0; i < n; ++i) f[i] = i;
    std::function<int(int)> Find = [&](int x) {
        return f[x] == x ? x : (f[x] = Find(f[x]));
    };
    std::vector<bool> Ans(q);
    for (auto [o, u, v, w, id] : Ed) {
        u = Find(u), v = Find(v);
        if (o == 0) {
            if (u != v) f[u] = v;
        } else {
            Ans[id] = u != v;
        }
    }
    for (bool ans : Ans) std::cout << (ans ? "Yes" : "No") << '\n';
    return 0;
}