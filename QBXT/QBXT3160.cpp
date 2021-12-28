#include <bits/stdc++.h>

using int64 = long long;

inline int64 Pow(int64 Base, int64 Exp, int64 Mod) {
    int64 Ret(1);
    while (Exp) {
        if (Exp & 1) Ret = Ret * Base % Mod;
        Base = Base * Base % Mod, Exp >>= 1;
    }
    return Ret;
}

inline int64 BSGS(int64 a, int64 b, int64 c) {
    if (b >= c) return -1;
    size_t T = ceil(sqrt(c));
    std::unordered_map<int64, size_t> Map;
    int64 s = 1, r = 1;
    for (size_t i = 0; i < T; ++i) Map[s * b % c] = i, s = s * a % c;
    for (size_t i = 1; i < T + 5; ++i) {
        if (Map.count(r = r * s % c)) {
            return Pow(a, i * T - Map[r], c) == b ? i * T - Map[r] : -1;
        }
    }
    return -1;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    int64 a, b, c;
    while (std::cin >> a >> b >> c) std::cout << BSGS(a, b, c) << '\n';
    return 0;
}