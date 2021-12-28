#include <bits/stdc++.h>

using uint64 = long long;

const int N = 2005;
const int P = 100000007;

int T, n, k;

uint64 Ans;
uint64 f[N], g[N], Phi[N];

inline uint64 Solve(size_t n, size_t k) {
    k = std::min(k, n - 1);
    g[1] = f[1] = 1;
    for (size_t i = 2; i <= n; ++i) {
        f[i] = g[i - 1];
        if (i > k + 2) f[i] = (f[i] + P - g[i - k - 2]) % P;
        g[i] = (f[i] + g[i - 1]) % P;
    }
    uint64 Ret = 0;
    for (size_t i = 0; i <= k && i < n; ++i) Ret += f[n - i] * (i + 1) % P;
    return Ret % P;
}

inline uint64 Pow(uint64 Base, uint64 Exp) {
    uint64 Ret(1);
    while (Exp) {
        if (Exp & 1) Ret = Ret * Base % P;
        Base = Base * Base % P, Exp >>= 1;
    }
    return Ret;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> T;
    Phi[1] = 1;
    for (int i = 2; i < N; ++i) {
        for (int j = 2;; ++j) {
            if (i % j == 0) {
                Phi[i] = Phi[i / j] * (j - bool(i / j % j));
                break;
            }
        }
    }
    while (T--) {
        std::cin >> n >> k;
        if (k > n) k = n;
        Ans = (k == n) * n;
        for (int i = 1; i <= n; ++i) {
            if (n % i) continue;
            Ans += Phi[i] * Solve(n / i, k) % P;
        }
        std::cout << Ans % P * Pow(n, P - 2) % P << std::endl;
    }
    return 0;
}