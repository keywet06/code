#include <bits/stdc++.h>

#define Deb std::cerr
#define Delin Deb << "[Debug] at Line " << __LINE__
#define Debug Delin << ": "
#define Deline Delin << std::endl

using int32 = int;
using int64 = long long;

inline int BiClz(int32 x) { return __builtin_clz(x); }
inline int BiCtz(int32 x) { return __builtin_ctz(x); }

inline int BiClm(int32 x) { return 32 - BiClz(x - 1); }
inline int BiBlm(int32 x) { return 1 << 32 - BiClz(x - 1); }

namespace Mods {

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
    int Ret = 1;
    while (Exp) {
        if (Exp & 1) Muls(Ret, Base);
        Sqrs(Base), Exp >>= 1;
    }
    return Ret;
}
inline int &Pows(int &Base, int Exp) { return Base = Pow(Base, Exp); }

inline int Inv(int x) { return Pow(x, P - 2); }
inline int Invs(int x) { return Pows(x, P - 2); }

#define templ template <typename... Args>

templ inline int Add(int x, int y, Args... args) { return Add(Add(x, y), args...); }
templ inline int Sub(int x, int y, Args... args) { return Sub(Sub(x, y), args...); }
templ inline int Mul(int x, int y, Args... args) { return Mul(Mul(x, y), args...); }
templ inline int &Adds(int &x, int y, Args... args) { return Adds(Adds(x, y), args...); }
templ inline int &Subs(int &x, int y, Args... args) { return Subs(Subs(x, y), args...); }
templ inline int &Muls(int &x, int y, Args... args) { return Muls(Muls(x, y), args...); }
templ inline void Sqrs(int &x, Args... args) { Sqrs(x), Sqrs(args...); }
templ inline int Pow(int Base, int Exp, Args... args) { return Pow(Pow(Base, Exp), args...); }
templ inline int &Pows(int &Base, int Exp, Args... args) { return Pows(Pows(Base, Exp), args...); }
templ inline void Invs(int &x, Args... args) { Invs(x), Invs(args...); }

#undef templ

}  // namespace Mods

using namespace Mods;

namespace Poly {

const int F = P - 1;
const int G = 3;

inline void NTT(int *f, int n, bool Flag) {
    const int N = 1 << 20;
    static struct NTTBase {
        int Rev[N], W[N];
        NTTBase(int n) {
            memset(Rev, 0, sizeof(Rev));
            memset(W, 0, sizeof(W));
            int c = BiCtz(n) - 1;
            for (int i = 1; i < n; ++i) Rev[i] = Rev[i >> 1] >> 1 | (i & 1) << c;
            int x = Pow(G, F >> c);
            W[n >> 1] = 1;
            for (int i = n >> 1 | 1; i < n; ++i) W[i] = Mul(W[i - 1], x);
            for (int i = (n >> 1) - 1; i >= 0; --i) W[i] = W[i << 1];
        }
    } Base(N);
    int Shift = BiCtz(N) - BiCtz(n = BiBlm(n));
    for (int i = 1, x; i < n; ++i) {
        if ((x = Base.Rev[i] >> Shift) > i) std::swap(f[x], f[i]);
    }
    for (int i = 1; i < n; i <<= 1) {
        for (int j = 0; j < n; j += i << 1) {
            for (int k = 0; k < i; ++k) {
                int x = f[j | k], y = Mul(Base.W[i << 1 | k], f[j | i | k]);
                f[j | k] = Add(x, y), f[j | i | k] = Sub(x, y);
            }
        }
    }
    if (Flag) {
        std::reverse(f + 1, f + n);
        int x = Inv(n);
        for (int i = 0; i < n; ++i) Muls(f[i], x);
    }
}

}  // namespace NTT

using namespace Poly;

const int N = 131072;
const int M = N << 1;
const int S = 1000;

int n, m, q;
int Ans[N], A[N];
int a0[M], a1[M], a2[M];

std::vector<int> Col[N + 1];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> m >> q;
    for (int i = 0; i < n; ++i) std::cin >> A[i];
    for (int i = 0, x; i < n; ++i) std::cin >> x, Col[x].push_back(i);
    int t = BiClm(n) + 1, T = BiBlm(n) << 1;
    for (int i = 1; i <= m; ++i) {
        std::vector<int> &V = Col[i];
        int l = V.size();
        if (l <= S) {
            for (int i = 0, I, J; i < l; ++i) {
                I = V[i];
                for (int j = i + 1; j < l; ++j) J = V[j], Adds(Ans[J - I], Mul(I + J + 2, Add(A[I], A[J])));
            }
            continue;
        }
        memset(a0, 0, sizeof(int) * T);
        memset(a1, 0, sizeof(int) * T);
        for (auto x : V) a0[x] = Mul(x + 1, A[x]), a1[n - x - 1] = 1;
        NTT(a0, T, false), NTT(a1, T, false);
        for (int i = 0; i < T; ++i) Adds(a2[i], Mul(a0[i], a1[i]));
        memset(a0, 0, sizeof(int) * T);
        memset(a1, 0, sizeof(int) * T);
        for (auto x : V) a0[x] = x + 1, a1[n - x - 1] = A[x];
        NTT(a0, T, false), NTT(a1, T, false);
        for (int i = 0; i < T; ++i) Adds(a2[i], Mul(a0[i], a1[i]));
    }
    NTT(a2, T, true);
    for (int i = 0; i < n; ++i) Adds(Ans[n - 1 - i], a2[i]);
    for (int i = n; i < 2 * n; ++i) Adds(Ans[i + 1 - n], a2[i]);
    for (int i = 1; i < q; ++i) {
        int Sum = 0;
        for (int j = i; j < n; j += i) Adds(Sum, Ans[j]);
        std::cout << Sum << " \n"[i == n - 1];
    }
    return 0;
}