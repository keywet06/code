#include <bits/stdc++.h>

using int32 = int;
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

inline int Pow(int Base, int64 Exp) {
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

template <typename T>
inline std::vector<T> Vector(size_t n) {
    return std::vector<T>(n);
}

template <typename T, typename... Args>
inline auto Vector(size_t n, Args... args) {
    return std::vector<decltype(Vector<T>(args...))>(n, Vector<T>(args...));
}

const int T3 = Inv(3);

inline int64 Health(int64 Poi, int64 Fir, int64 Rep) {
    if (!Poi && !Fir) return 0;
    if (!Poi) return 2 * (Fir + Rep);
    if (!Fir) return Poi + Rep * 2 - 1;
    return Poi - 1 + (Fir + Rep) * 3 + Rep;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int T;
    std::cin >> T;
    while (T--) {
        int n;
        std::cin >> n;
        auto f = Vector<int>(n + 2, n / 2 + 2, n / 2 + 2);
        f[0][0][n / 2 + 1] = Div(3, 2);
        for (int i = n + 1; i >= 0; --i) {
            for (int j = n / 2 + 1; j >= 0; --j) {
                for (int k = n / 2 + 1 - (i == 0 && j == 0); k >= 0; --k) {
                    if (Health(i, j, k) >= n) continue;
                    f[i][j][k] = Add(Mul(Add(f[i + 1][j][k], f[i][j + 1][k], f[i][j][k + 1]), T3), 1);
                }
            }
        }
        std::cout << f[0][0][0] << std::endl;
    }
    return 0;
}