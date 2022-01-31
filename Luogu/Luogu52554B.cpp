#include <bits/stdc++.h>

using int64 = long long;

const int P = 998244353;

inline int Add(int x, int y) { return (x += y) >= P ? x - P : x; }
inline int Sub(int x, int y) { return (x -= y) < 0 ? x + P : x; }
inline int Mul(int x, int y) { return int64(x) * y % P; }
inline int &Adds(int &x, int y) { return (x += y) >= P ? x -= P : x; }
inline int &Subs(int &x, int y) { return (x -= y) < 0 ? x += P : x; }
inline int &Muls(int &x, int y) { return x = int64(x) * y % P; }

inline int Pow(int Base, int Exp) {
    int Ret(1);
    while (Exp) {
        if (Exp & 1) Muls(Ret, Base);
        Muls(Base, Base), Exp >>= 1;
    }
    return Ret;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int n, k;
    std::cin >> n >> k;
    std::vector<int> a(n), b(n);
    int SumA = 0, SumB = 0, Sum = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i], Adds(SumA, Adds(a[i] %= P, P));
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i], Adds(SumB, Adds(b[i] %= P, P));
    }
    for (int i = 0; i < n; ++i) Adds(Sum, Mul(a[i], b[i]));
    if (k == 0) return std::cout << n << std::endl, 0;
    std::cout << Mul(Pow(Sum, k - 1), Mul(SumA, SumB)) << std::endl;
    return 0;
}
