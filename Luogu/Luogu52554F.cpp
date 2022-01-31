#include <bits/stdc++.h>

using int64 = long long;

const int P = 998244353;

inline int Mul(int x, int y) { return int64(x) * y % P; }
inline int &Muls(int &x, int y) { return x = int64(x) * y % P; }

template <typename... Args>
inline int Mul(int x, int y, Args... args) {
    return Mul(Mul(x, y), args...);
}

inline int Pow(int Base, int Exp) {
    int Ret(1);
    while (Exp) {
        if (Exp & 1) Muls(Ret, Base);
        Muls(Base, Base), Exp >>= 1;
    }
    return Ret;
}

inline int Inv(int x) { return Pow(x, P - 2); }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int a, b, c;
    std::cin >> a >> b >> c;
    int n = a + b + c;
    std::vector<int> Fac(n + 1);
    Fac[0] = Fac[1] = 1;
    for (int i = 2; i <= n; ++i) Fac[i] = Mul(Fac[i - 1], i - 1);
    for (int i = 1; i <= n; ++i) Muls(Fac[i], Fac[i - 1]);
    std::cout << Mul(Fac[a], Fac[b], Fac[c], Fac[n], Inv(Fac[a + b]),
                     Inv(Fac[a + c]), Inv(Fac[b + c]))
              << std::endl;
    return 0;
}