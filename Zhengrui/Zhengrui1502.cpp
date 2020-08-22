#include <bits/stdc++.h>
const int N = 100100;
const int M = 111;
const int mod = 998244353;
typedef long long ll;
int ksm(ll a, int b, int c = 1) {
    for (; b; b /= 2, a = a * a % mod) {
        if (b & 1) c = c * a % mod;
    }
    return c;
}
int jc[N], jc2[N], S[M][M];
void Init(int d) {
    jc[0] = 1;
    for (int i = 1; i < N; ++i) jc[i] = (ll)jc[i - 1] * i % mod;
    jc2[N - 1] = ksm(jc[N - 1], mod - 2);
    for (int i = N - 1; i; --i) jc2[i - 1] = (ll)jc2[i] * i % mod;
    S[0][0] = 1;
    for (int i = 1; i < M; ++i) {
        S[i][0] = (ll)S[i - 1][0] * d % mod;
        for (int j = 1; j <= i; ++j) {
            S[i][j] =
                ((ll)S[i - 1][j] * (d - j + mod) + mod - S[i - 1][j - 1]) % mod;
        }
    }
}

int f[N], g[N], a[N];
std::vector<int> G[N];
void dfs(int x, int u, int v, int fa = -1) {
    if (a[x]) {
        f[x] = 1;
        g[x] = 0;
    } else {
        f[x] = g[x] = 1;
    }
    for (int i : G[x]) {
        if (i != fa) {
            dfs(i, u, v, x);
            f[x] = (ll)((ll)f[i] * (u - 1) + (ll)g[i] * v) % mod * f[x] % mod;
            g[x] = (ll)((ll)f[i] * u + (ll)g[i] * (v - 1)) % mod * g[x] % mod;
        }
    }
}
int n, m, K, cnt, ans;
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m >> K >> cnt;
    Init(m);
    for (int i = 1; i <= cnt; ++i) {
        int x;
        std::cin >> x;
        a[x] = 1;
    }
    for (int i = 1; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    for (int i = 0; i <= K && i <= m; ++i) {
        memset(f, 0, sizeof f);
        memset(g, 0, sizeof g);
        dfs(1, m - i, i);
        int res = ((ll)f[1] * (m - i) + (ll)g[1] * i) % mod;
        res = (ll)res * jc[m] % mod * jc2[m - i] % mod;
        ans = (ans + (ll)res * S[K][i]) % mod;
    }
    std::cout << ans << std::endl;
    return 0;
}