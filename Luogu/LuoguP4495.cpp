#include <bits/stdc++.h>

#define fi first
#define se second

using int64 = long long;

const int P = 1000000007;
const int N = 1000005;

int n, q, p, cnt, r, x, y, z;
int v[N], w[N], c[N], d[N], f[N], dp[N];

std::map<int, int> s, map, ans;

auto gcd = std::__gcd<int>;

inline int mul(int x, int y) { return int64(x) * y % P; }

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> q >> p;
    for (int i = 1; i <= n; ++i) std::cin >> v[i], ++s[v[i] = gcd(v[i], p)];
    d[0] = 1;
    for (int i = 1; i < N; ++i) d[i] = d[i - 1] * 2 % P;
    c[map[p] = ++cnt] = p, dp[cnt] = 1;
    for (auto e : s) {
        r = cnt;
        for (int i = 1; i <= r; ++i) {
            if (!(y = map[x = gcd(c[i], e.fi)])) c[y = map[x] = ++cnt] = x;
            f[y] = (f[y] + mul(dp[i], d[e.se] - 1)) % P;
        }
        for (int i = 1; i <= cnt; ++i) dp[i] = (dp[i] + f[i]) % P, f[i] = 0;
    }
    s.clear();
    for (int i = 1; i <= q; ++i) std::cin >> w[i], ++s[w[i] = gcd(w[i], p)];
    for (auto e : s) {
        x = 0;
        for (int i = 1; i <= cnt; ++i) {
            if (e.fi % c[i] == 0) x = (x + dp[i]) % P;
        }
        ans[e.fi] = x;
    }
    for (int i = 1; i <= q; ++i) std::cout << ans[w[i]] << '\n';
    return 0;
}