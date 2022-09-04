#include <bits/stdc++.h>

const int C = 30;

int n, Zero;
int Num[C];

std::vector<std::pair<int, int> > Oper;

inline void Split(int n, int k) {
    int m = 1 << 31 - __builtin_clz(n);
    if (m < n) {
        for (int j = 1; j <= n - m; ++j) Oper.emplace_back(m - j << k, m + j << k);
        Num[__builtin_ctz(m) + k + 1] += n - m, Split(n - m, k + 1);
    }
    ++Num[__builtin_ctz(m) + k];
    if (2 * m - n > 1) Split(2 * m - n - 1, k);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n;
    if (n == 1) return std::cout << "1 0\n", 0;
    Split(n, 0);
    int p = 0;
    while (p < C && Num[p] < 2) ++p;
    if (p == C) return std::cout << -1 << '\n', 0;
    Oper.emplace_back(1 << p, 1 << p);
    ----Num[p], ++Num[p + 1], ++Zero;
    int t = C - 1;
    while (t >= 0 && !Num[t]) --t;
    for (int i = 0; i < t; ++i) {
        while (Num[i]) {
            if (Num[i] >= 2) {
                ----Num[i], ++Num[i + 1], ++Zero, Oper.emplace_back(1 << i, 1 << i);
            } else {
                --Zero, ++Num[i], Oper.emplace_back(0, 1 << i);
            }
        }
    }
    while (Zero) --Zero, ++Num[t], Oper.emplace_back(0, 1 << t);
    std::cout << (1 << t) << ' ' << Oper.size() << '\n';
    for (auto [x, y] : Oper) std::cout << x << ' ' << y << '\n';
    return 0;
}