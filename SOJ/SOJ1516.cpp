#include <bits/stdc++.h>

using int64 = long long;

const int P = 998244353;

inline int Add(int x, int y) { return (x += y) >= P ? x - P : x; }
inline int Sub(int x, int y) { return (x -= y) < 0 ? x + P : x; }
inline int Mul(int x, int y) { return int64(x) * y % P; }
inline int &Adds(int &x, int y) { return (x += y) >= P ? x -= P : x; }
inline int &Subs(int &x, int y) { return (x -= y) < 0 ? x += P : x; }
inline int &Muls(int &x, int y) { return x = int64(x) * y % P; }

inline int Sqr(int x) { return Mul(x, x); }
inline int &Sqrs(int &x) { return Muls(x, x); }

inline int Pow(int Base, int Exp) {
    int Ret(1);
    while (Exp) {
        if (Exp & 1) Muls(Ret, Base);
        Sqrs(Base), Exp >>= 1;
    }
    return Ret;
}

inline int Inv(int x) { return Pow(x, P - 2); }

inline int &Pows(int &Base, int Exp) { return Base = Pow(Base, Exp); }
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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int n, r;
    std::cin >> n >> r;
    std::vector<int> a(r);
    for (int i = 0; i < r; ++i) std::cin >> a[i];
    a.push_back(a.front() + n);
    std::vector<int> f(n + 1);
    for (int i = 1, s = 0; i <= n; ++i) Adds(s, f[i] = Add(Div(s, i), 2));
    for (int i = 1; i <= n; ++i) Adds(f[i], f[i - 1]);
    for (int i = 1; i <= n; ++i) Divs(f[i], i + 1);
    int Ans = 0;
    for (int i = 0; i < r; ++i) Adds(Ans, f[a[i + 1] - a[i] - 1], 1);
    std::cout << Ans << std::endl;
    return 0;
}