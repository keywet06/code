#include <bits/stdc++.h>
const int mod = 998244353;
const int M = 100000;
const int Mp = M + 5;
long long m, n, c, ans;
long long k[Mp];
inline long long power(long long x, int y) {
    return y ? power(x * x % mod, y / 2) * (y & 1 ? x : 1) % mod : 1;
}
inline void dfs(int u, long long val) {
    if (u == m + 1) {
        (ans += n ? 0 : val) %= mod;
        return;
    }
    for (int i = 1; i <= n; ++i) {
        n -= i;
        dfs(u + 1, (val + power(i, k[u])) % mod);
        n += i;
    }
}
int main() {
    std::cin >> m >> n;
    for (int i = 1; i <= m; ++i) {
        std::cin >> k[i];
    }
    if (m == 1) {
        std::cout << power(n, k[1]) << std::endl;
        return 0;
    }
    dfs(1, 0);
    std::cout << ans << std::endl;
    return 0;
}