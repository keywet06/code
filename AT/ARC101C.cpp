#include <bits/stdc++.h>
const int N = 5005;
const long long mod = 1000000007;
int n, x, y;
int size[N];
long long tmp[N], df[N];
long long f[N][N];
std::vector<int> to[N];
inline void dfs(int u, int fa) {
    f[u][1] = 1;
    size[u] = 1;
    for (auto v: to[u]) {
        if (v == fa) continue;
        dfs(v, u);
        for (int i = 0; i <= size[u]; ++i) tmp[i] = f[u][i], f[u][i] = 0;
        for (int i = 0; i <= size[u]; ++i) {
            for (int j = 0; j <= size[v]; ++j) {
                f[u][i + j] += tmp[i] * f[v][j] % mod;
            }
        }
        size[u] += size[v];
        for (int i = 0; i <= size[u]; ++i) ((f[u][i] %= mod) += mod) %= mod;
    }
    for (int i = 2; i <= size[u]; i += 2) f[u][0] += -df[i - 1] * f[u][i] % mod;
    ((f[u][0] %= mod) += mod) %= mod;
}
int main() {
    std::cin >> n;
    for (int i = 1; i < n; ++i) {
        std::cin >> x >> y;
        to[x].push_back(y);
        to[y].push_back(x);
    }
    df[0] = df[1] = 1;
    for (int i = 2; i <= n; ++i) df[i] = df[i - 2] * i % mod;
    dfs(1, 1);
    std::cout << mod - f[1][0] << std::endl;
    return 0;
}