#include <bits/stdc++.h>

using int64 = long long;

int k, n, m;

inline double Pow(double Base, int Exp) {
    double Ret(1);
    while (Exp) {
        if (Exp & 1) Ret *= Base;
        Base *= Base, Exp >>= 1;
    }
    return Ret;
}

inline double Get(int n, int x) {
    return double((x + 1) * (n - x) * 2 - 1) / n / n;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> k >> n >> m;
    double Ans = 0;
    for (int64 i = 0; i < n; ++i) {
        for (int64 j = 0; j < m; ++j) {
            Ans += 1 - Pow(1 - Get(n, i) * Get(m, j), k);
        }
    }
    std::cout << int(Ans + 0.5 + 1e-8) << std::endl;
    return 0;
}