#include <bits/stdc++.h>

using int64 = long long;

const int N = 1000005;
const int P = 1000000007;

int n, x, y, ans, t;
int a[N], v[N], f[N];

inline int mul(const int x, const int y) { return int64(x) * y % P; }

inline int power(int x, int y) {
    int ret = 1;
    while (y) {
        if (y & 1) ret = mul(ret, x);
        x = mul(x, x), y >>= 1;
    }
    return ret;
}

void solve() {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> a[i], v[i] = 0;
    ans = f[1] = f[2] = f[3] = f[4] = 0;
    for (int i = 1; i <= n; ++i) {
        if (v[i]) continue;
        x = a[i], y = 1, v[x] = 1;
        while (x != i) ++y, x = a[x], v[x] = 1;
        if (y > 4) f[3] += t = (y - 4) / 3, y -= t * 3, ans += t;
        if (y) ++f[y];
    }
    if (n % 3 == 0) {
        ans += f[4], f[1] += f[4], f[4] = 0;
        
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    int T;
    std::cin >> T;
    while (T--) solve();
    return 0;
}