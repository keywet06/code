#include <bits/stdc++.h>

using ldouble = double;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    int n;
    std::cin >> n;
    std::vector<std::vector<std::pair<int, ldouble> > > To(n);
    for (int i = 1, x, y, z; i < n; ++i) {
        std::cin >> x >> y >> z, --x, --y, z = 100 - z;
        To[x].emplace_back(y, ldouble(z) / 100);
        To[y].emplace_back(x, ldouble(z) / 100);
    }
    std::vector<ldouble> q(n);
    for (ldouble &x : q) std::cin >> x, x = (100 - x) / 100;
    std::vector<ldouble> f(n), g(n), Up(n);
    auto Get = [](ldouble x, ldouble y) { return x + y - x * y; };
    using DfsType = std::function<void(int, int)>;
    DfsType Dfs1 = [&](int u, int Fa) {
        f[u] = q[u];
        for (auto [v, Val] : To[u]) {
            if (v == Fa) continue;
            Up[v] = Val, Dfs1(v, u);
            f[u] *= Get(f[v], Val);
        }
    };
    Dfs1(0, -1);
    DfsType Dfs2 = [&](int u, int Fa) {
        std::vector<int> T;
        std::vector<ldouble> R;
        for (auto [v, Val] : To[u]) {
            if (v != Fa) T.push_back(v), R.push_back(Val);
        }
        int n = T.size();
        if (!n) return;
        ldouble F = Fa == -1 ? q[u] : q[u] * g[u];
        if (n == 1) {
            g[T.front()] = Get(F, R.front());
            Dfs2(T.front(), u);
            return;
        }
        std::vector<ldouble> Le(n), Ri(n);
        Le.front() = Get(f[T.front()], R.front());
        for (int i = 1; i < n; ++i) {
            Le[i] = Le[i - 1] * Get(f[T[i]], R[i]);
        }
        Ri.back() = Get(f[T.back()], R.back());
        for (int i = n - 2; i >= 0; --i) {
            Ri[i] = Ri[i + 1] * Get(f[T[i]], R[i]);
        }
        g[T.front()] = Get(F * Ri[1], R.front());
        g[T.back()] = Get(F * Le[n - 2], R.back());
        for (int i = 1; i <= n - 2; ++i) {
            g[T[i]] = Get(F * Le[i - 1] * Ri[i + 1], R[i]);
        }
        for (auto v : T) Dfs2(v, u);
    };
    Dfs2(0, -1);
    ldouble Ans = 1 - f[0];
    std::cout << std::fixed << std::setprecision(6);
    for (int i = 1; i < n; ++i) Ans += 1 - f[i] * g[i];
    std::cout << Ans << std::endl;
    return 0;
}