#include <bits/stdc++.h>

using int64 = long long;
using int128 = __int128;

const int64 INF = int64(1e18) + 5;

inline int64 Pow(int128 x, int m) {
    int128 Ret = 1;
    while (m) {
        if (m & 1) Ret = Ret * x;
        if (x > INF || Ret > INF) return INF;
        x = x * x, m >>= 1;
    }
    return Ret;
}

const int C = 70;

int mu[C];

int64 n, ans;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    mu[1] = -1;
    for (int i = 2; i < C; ++i) {
        for (int j = 2; j <= i; ++j) {
            if (i % j == 0) {
                mu[i] = i / j % j ? -mu[i / j] : 0;
                break;
            }
        }
    }
    for (int i = 2; Pow(2, i) <= n; ++i) {
        int64 l = 1, r = i <= 5 ? 1e9 : 1e3, mid;
        while (l < r) {
            mid = l + r + 1 >> 1;
            if (Pow(mid, i) <= n) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }
        ans += mu[i] * (l - 1);
    }
    std::cout << ans + 1 << std::endl;
    return 0;
}