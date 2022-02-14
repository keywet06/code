#include <bits/stdc++.h>

using int64 = long long;

const int P = 998244353;
const int F = P - 1;

inline int Add(int x, int y) { return (x += y) >= P ? x - P : x; }
inline int Sub(int x, int y) { return (x -= y) < 0 ? x + P : x; }
inline int Mul(int x, int y) { return int64(x) * y % P; }
inline int &Adds(int &x, int y) { return (x += y) >= P ? (x -= P) : x; }
inline int &Subs(int &x, int y) { return (x -= y) < 0 ? (x += P) : x; }
inline int &Muls(int &x, int y) { return x = int64(x) * y % P;}

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
    int n;
    std::cin >> n;
    std::vector<std::vector<int> > a(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) std::cin >> a[i][j], Adds(a[i][j], P);
    }
    int Ans = 1;
    for (int i = 0, c = 0; i < n; c = ++i) {
        while (c + 1 < n && a[c][i] == 0) ++c;
        if (c != i) a[i].swap(a[c]), Muls(Ans, F);
        Muls(Ans, a[i][i]);
        int x = Inv(a[i][i]);
        for (int j = i; j < n; ++j) Muls(a[i][j], x);
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            int x = Sub(0, a[j][i]);
            for (int k = i; k < n; ++k) Adds(a[j][k], Mul(x, a[i][k]));
        }
    }
    for (int i = 1; i <= n / 2; ++i) Muls(Muls(Ans, i * 2), i * 2);
    std::cout << Ans << std::endl;
    return 0;
}