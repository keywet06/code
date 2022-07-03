#include <bits/stdc++.h>

#define Deb std::cerr
#define Delin Deb << "[Debug] at Line " << __LINE__
#define Debug Delin << " : "
#define Deline Delin << std::endl

using int32 = int;
using int64 = long long;
using lint64 = long;
using uint32 = unsigned int;
using uint64 = unsigned long long;
using ulint64 = unsigned long;

namespace Bits {

#define Bi32(i32)                                                       \
    inline constexpr int BiFfs(i32 x) { return __builtin_ffs(x); }      \
    inline constexpr int BiClz(i32 x) { return __builtin_clz(x); }      \
    inline constexpr int BiCtz(i32 x) { return __builtin_ctz(x); }      \
    inline constexpr int BiPop(i32 x) { return __builtin_popcount(x); } \
    inline constexpr int BiPar(i32 x) { return __builtin_parity(x); }

#define Bi64(i64)                                                         \
    inline constexpr int BiFfs(i64 x) { return __builtin_ffsll(x); }      \
    inline constexpr int BiClz(i64 x) { return __builtin_clzll(x); }      \
    inline constexpr int BiCtz(i64 x) { return __builtin_ctzll(x); }      \
    inline constexpr int BiPop(i64 x) { return __builtin_popcountll(x); } \
    inline constexpr int BiPar(i64 x) { return __builtin_parityll(x); }

Bi32(int32) Bi32(uint32) Bi64(int64) Bi64(uint64)

#undef Bi32
#undef Bi64

}  // namespace Bits

namespace Mods {

const int P = 998244353;
const int G = 3;

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

inline int Inv(int x) { return Pow(x, P - 2); }

inline int Div(int x, int y) { return Mul(x, Inv(y)); }
inline int &Divs(int &x, int y) { return Muls(x, Inv(y)); }

#define templ template <typename... Args>
templ inline int Add(int x, int y, Args... args) { return Add(Add(x, y), args...); }
templ inline int Sub(int x, int y, Args... args) { return Sub(Sub(x, y), args...); }
templ inline int Mul(int x, int y, Args... args) { return Mul(Mul(x, y), args...); }
templ inline int Div(int x, Args... args) { return Mul(x, Inv(Mul(args...))); }
templ inline int &Adds(int &x, int y, Args... args) { return Adds(Adds(x, y), args...); }
templ inline int &Subs(int &x, int y, Args... args) { return Subs(Subs(x, y), args...); }
templ inline int &Muls(int &x, int y, Args... args) { return Muls(Muls(x, y), args...); }
templ inline int &Divs(int &x, Args... args) { return Muls(x, Inv(Mul(args...))); }
#undef templ

}  // namespace Mods

using namespace Bits;
using namespace Mods;

const int N = 300005;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int T;
    std::cin >> T;
    while (T--) {
        int64 g, l;
        std::cin >> g >> l;
        int64 t = l / g, Bl = 1, Br = 1e9, Mid;
        while (Bl < Br) Mid = Bl + Br >> 1, Mid * Mid >= t ? Br = Mid : Bl = Mid + 1;
        std::cout << 2 * g * Bl << ' ' << g + l << '\n';
    }
    return 0;
}