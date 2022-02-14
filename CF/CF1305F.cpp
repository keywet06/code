#include <bits/stdc++.h>

using int64 = long long;
using int128 = __int128;

struct Primes {
    std::vector<int> Vis, Pr;
};

inline Primes &Pr() {
    static Primes P;
    return P;
}

template <typename BType, typename EType, typename MType>
inline BType Pow(BType Base, EType Exp, MType Mod) {
    BType Ret(1);
    while (Exp) {
        if (Exp & 1) Ret *= Base;
        Base *= Base, Exp >>= 1;
    }
    return Ret;
}

inline bool MillerRabin(int64 n) {
    const int Test[8] = {2, 3, 5, 7, 11, 13, 82, 373};
    if (n <= 2) return n == 2;
    int128 p = n - 1;
    int e = 0;
    while (!(p & 1)) p /= 2, ++e;
    for (int x : Test) {
        if (n % x == 0) {
            if (n == x) continue;
            return false;
        }
        int128 u = Pow(int128(x), p, n);
        if (u == 1) continue;
        for (int i = 0; i < e; ++i) {
            if (u == n - 1) break;
            u = u * u % n;
            if (u == 1) return false;
        }
        if (u != n - 1) return false;
    }
    return true;
}

inline int64 PollardRho(int64 n) {
    
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);

    return 0;
}
