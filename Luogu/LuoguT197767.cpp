#include <bits/stdc++.h>

using int64 = long long;

const int N = 5000005;
const int P = 998244353;

int T, n, m, k;

int64 fac[N], inv[N], caf[N];

inline int64 C(int64 m, int64 n) {
    if (m < n || n < 0 || m < 0) return 0;
    return fac[m] * caf[n] % P * caf[m - n] % P;
}

inline int64 solve(int n, int m, int64 k) {
    if (n <= 1) return fac[std::max(n + m - 1, 0)];
    return C(m - n * k + n - 1, n - 1) * fac[n - 1] % P * fac[m] % P;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    fac[0] = inv[0] = inv[1] = caf[0] = 1;
    for (int i = 1; i < N; ++i) fac[i] = fac[i - 1] * i % P;
    for (int i = 2; i < N; ++i) inv[i] = (P - P / i) * inv[P % i] % P;
    for (int i = 1; i < N; ++i) caf[i] = caf[i - 1] * inv[i] % P;
    std::cin >> T;
    while (T--) std::cin >> n >> m >> k, std::cout << solve(n, m, k) << '\n';
    return 0;
}