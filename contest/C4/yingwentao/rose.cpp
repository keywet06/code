#include <bits/stdc++.h>

#define debug std::cerr << "Debug(" << __LINE__ << "): "

inline void ios(std::string s) {
    std::string t;
    freopen((s + ".in").data(), "r", stdin);
    freopen((s + ".out").data(), "w", stdout);
}

const int B = 2;
const int N = 300005;

int n, m, x, y, z, r;
int fd[N], g[N], f[N], fu[N], fa[N], ans[N];
int s[N][B];

inline void dfs(int u, int n, int d) {
    int t = f[d], p;
    if (n == m) ++f[d - m], n = fa[n], fu[d - m] = u;
    if (p = n, s[u][0]) {
        while (p && g[p + 1]) p = fa[p];
        dfs(s[u][0], p += !g[p + 1], d + 1);
    }
    if (p = n, s[u][1]) {
        while (p && !g[p + 1]) p = fa[p];
        dfs(s[u][1], p += g[p + 1], d + 1);
    }
    if (f[d] > t) ans[u] = fu[d];
}

int main() {
    ios("rose");
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i < n; ++i) std::cin >> x >> y >> z, s[x][z] = y, fd[y] = 1;
    for (int i = 1; i <= n; ++i) r = fd[i] ? r : i;
    std::cin >> m;
    for (int i = 1; i <= m; ++i) std::cin >> g[i];
    fa[1] = 0;
    for (int i = 2; i <= n; ++i) {
        fa[i] = fa[i - 1];
        while (fa[i] && g[fa[i] + 1] != g[i]) fa[i] = fa[fa[i]];
        fa[i] += g[fa[i] + 1] == g[i];
    }
    dfs(r, 0, 1);
    for (int i = 1; i <= n; ++i) std::cout << ans[i] << ' ';
    std::cout << std::endl;
    return 0;
}