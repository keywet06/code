#include <bits/stdc++.h>

using int64 = long long;

const int Q = 1005;
const int N = 100000;

int T;

int64 n, k, l, r, d, x, ans;
int64 g[Q];
int64 f[N];

inline int64 sqr(int64 x) { return x * x; }
inline int64 tqr(int64 x) { return x * x * x; }

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> T;
    for (int i = 1; i < N; ++i) f[i] = f[i - 1] + (i << 1 | 1) * i;
    for (int i = 1; i < Q; ++i) g[i] = g[i - 1] + (tqr(i + 1) - tqr(i)) * i;
    while (T--) {
        std::cin >> n >> k;
        if (k == 1) {
            std::cout << n * (n + 1) / 2 << '\n';
        } else if (k == 2) {
            l = 2, r = N;
            while (l < r) d = l + r >> 1, n < sqr(d) ? r = d : l = d + 1;
            std::cout << f[l - 2] + (n - sqr(l - 1) + 1) * (l - 1) << '\n';
        } else if (k == 3) {
            l = 2, r = Q;
            while (l < r) d = l + r >> 1, n < tqr(d) ? r = d : l = d + 1;
            std::cout << g[l - 2] + (n - tqr(l - 1) + 1) * (l - 1) << '\n';
        } else {
            d = r = ans = 0;
            while (++d) {
                for (x = l = 1; x <= k && l <= n; ++x) l = l * (d + 1);
                if (l > n && (ans += (n - r) * d)) break;
                ans += (--l - r) * d, r = l;
            }
            std::cout << ans << '\n';
        }
    }
    return 0;
}