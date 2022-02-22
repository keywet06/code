#include <bits/stdc++.h>

using int64 = long long;

const int P = 1000000007;

inline int Add(int x, int y) { return (x += y) >= P ? x - P : x; }
inline int Sub(int x, int y) { return (x -= y) < 0 ? x + P : x; }
inline int Mul(int x, int y) { return int64(x) * y % P; }
inline int &Adds(int &x, int y) { return (x += y) >= P ? x -= P : x; }
inline int &Subs(int &x, int y) { return (x -= y) < 0 ? x += P : x; }
inline int &Muls(int &x, int y) { return x = int64(x) * y % P; }

inline int Sqr(int x) { return Mul(x, x); }
inline int &Sqrs(int &x) { return Muls(x, x); }

inline int Pow(int Base, int64 Exp) {
    if (Exp < 0) return 0;
    int Ret(1);
    while (Exp) {
        if (Exp & 1) Muls(Ret, Base);
        Sqrs(Base), Exp >>= 1;
    }
    return Ret;
}

inline int Inv(int x) { return Pow(x, P - 2); }

inline int &Pows(int &Base, int64 Exp) { return Base = Pow(Base, Exp); }
inline int &Invs(int &x) { return Pows(x, P - 2); }

inline int Div(int x, int y) { return Mul(x, Inv(y)); }
inline int &Divs(int &x, int y) { return Muls(x, Inv(y)); }

#define templ template <typename... Args>

templ int Add(int x, int y, Args... args) { return Add(Add(x, y), args...); }
templ int Sub(int x, int y, Args... args) { return Sub(Sub(x, y), args...); }
templ int Mul(int x, int y, Args... args) { return Mul(Mul(x, y), args...); }
templ int Div(int x, Args... args) { return Mul(x, Inv(Mul(args...))); }
templ int &Adds(int &x, int y, Args... args) { return Adds(Adds(x, y), args...); }
templ int &Subs(int &x, int y, Args... args) { return Subs(Subs(x, y), args...); }
templ int &Muls(int &x, int y, Args... args) { return Muls(Muls(x, y), args...); }
templ int &Divs(int &x, Args... args) { return Muls(x, Inv(Mul(args...))); }

#undef templ

inline int PF(int x) { return x & 1 ? P - 1 : 1; }
inline int Mod(int64 x) { return x % P; }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<int> Ha(n), Hb(m);
    for (int i = 0; i < n; ++i) std::cin >> Ha[i];
    for (int i = 0; i < m; ++i) std::cin >> Hb[i];
    std::sort(Ha.begin(), Ha.end(), std::greater<int>());
    std::sort(Hb.begin(), Hb.end(), std::greater<int>());
    int T = std::max(n, m);
    std::vector<int> Fac(T + 1), Far(T + 1);
    Fac[0] = 1;
    for (int i = 1; i <= T; ++i) Fac[i] = Mul(Fac[i - 1], i);
    Far[T] = Inv(Fac[T]);
    for (int i = T - 1; i >= 0; --i) Far[i] = Mul(Far[i + 1], i + 1);
    auto C = [&](int m, int n) -> int { return Mul(Fac[m], Far[n], Far[m - n]); };
    int64 Sx = 0, Sy = 0, Ba = 0, Bb = 0;
    int Ans = 0, Num = 1;
    while (Ba < n || Bb < m) {
        int A = std::max(Ba == n ? 0 : Ha[Ba], Bb == m ? 0 : Hb[Bb]) + 1, B = A - 1;
        int64 Nx = 0, Ny = 0;
        while (Ba < n && Ha[Ba] == B) ++Ba, ++Nx;
        while (Bb < m && Hb[Bb] == B) ++Bb, ++Ny;
        int Sum = 0, Sun = 0, Saa = Div(A - 1, 2), Sbb = Div(B - 1, 2);
        for (int x = 0; x <= Nx; ++x) {
            int64 Ca = (Nx - x) * Sy, Cb = x * (Sy + Ny), D = Nx + Sx - x;
            Adds(Sum, Mul(Pow(A, Ca), Pow(B, Cb), Pow(Sub(Pow(A, D), Pow(B, D)), Ny), PF(x), C(Nx, x)));
            Adds(Sun, Mul(Pow(A, Ca), Pow(B, Cb),
                          Add(Mul(Add(Mul(Mod(Ca), Saa), Mul(Ny, D, Saa), Mul(Mod(Cb), Sbb)),
                                  Pow(Sub(Pow(A, D), Pow(B, D)), Ny)),
                              Mul(D, Sub(Saa, Sbb), Ny, Pow(B, D), Pow(Sub(Pow(A, D), Pow(B, D)), Ny - 1))),
                          PF(x), C(Nx, x)));
        }
        Adds(Ans, Div(Sun, Sum)), Muls(Num, Sum);
        Sx += Nx, Sy += Ny;
    }
    std::cout << Muls(Ans, Num) << std::endl;
    return 0;
}