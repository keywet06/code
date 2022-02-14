#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    int n;
    std::cin >> n;
    std::vector<int> a(n), b(n), ra(n), rb(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i], ra[--a[i]] = i;
    for (int i = 0; i < n; ++i) std::cin >> b[i], rb[--b[i]] = i;
    std::vector<std::vector<int> > To(n);
    for (int i = 1, u, v; i < n; ++i) {
        std::cin >> u >> v, --u, --v;
        To[u].push_back(v);
        To[v].push_back(u);
    }
    std::vector<int> d(a), rd(ra);
    int r = rb[0];
    using DfsType = std::function<void(int, int)>;
    std::vector<int> Fa(n);
    DfsType Dfs1 = [&](int u, int f) {
        Fa[u] = f;
        for (int v : To[u]) {
            if (v != f) Dfs1(v, u);
        }
    };
    Dfs1(r, -1);
    std::vector<int> Li;
    for (int u = rd[0]; u != r; u = Fa[u]) Li.push_back(u);
    
    return 0;
}