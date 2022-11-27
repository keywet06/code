#include <bits/stdc++.h>

using int64 = long long;

namespace FastIO {

const int T = 1 << 15;
char buf[T], *p1 = buf, *p2 = buf;
inline char FastReadChar() { return p1 == p2 && (p2 = buf + fread(p1 = buf, 1, T, stdin), p1 == p2) ? -1 : *p1++; }

int64 Read() {
    int64 x = 0;
    char c;
    bool s = 0;
    do c = FastReadChar();
    while (c != 45 && (c < 48 || c > 57));
    if (c == 45) c = FastReadChar(), s = 1;
    do x = 10 * x + (c & 15), c = FastReadChar();
    while (c >= 48 && c <= 57);
    return s ? -x : x;
}

};  // namespace FastIO


#ifndef OCT_MODINT_HPP
#define OCT_MODINT_HPP

namespace Oct {

template <typename Type, Type P, typename MulType = Type>
class ModInt {
   protected:
    Type x;

   public:
    using Self = ModInt<Type, P, MulType>;
    ModInt() : x(0) {}
    ModInt(Type c) : x(c) {}
    explicit operator Type() { return x; }
    Type &Data() { return x; }
    friend Self operator+(Self a, Self b) { return (a.x += b.x) >= P ? a.x - P : a.x; }
    friend Self operator-(Self a, Self b) { return (a.x -= b.x) < 0 ? a.x + P : a.x; }
    friend Self operator*(Self a, Self b) { return MulType(a.x) * b.x % P; }
    friend Self &operator+=(Self &a, Self b) { return (a.x += b.x) >= P ? a.x -= P, a : a; }
    friend Self &operator-=(Self &a, Self b) { return (a.x -= b.x) < 0 ? a.x += P, a : a; }
    friend Self &operator*=(Self &a, Self b) { return a.x = MulType(a.x) * b.x % P, a; }
#define templ template <typename ExpType>
    templ Self Pow(ExpType Exp) const {
        Self Base(*this), Ret(1);
        while (Exp) {
            if (Exp & 1) Ret *= Base;
            Base *= Base, Exp >>= 1;
        }
        return Ret;
    }
    templ Self &Pows(ExpType Exp) { return *this = Pow(Exp); }
    templ Self &PowEq(ExpType Exp) { return Pows(Exp); }
    templ Self &PowEqual(ExpType Exp) { return Pows(Exp); }
    templ friend Self Pow(Self Base, ExpType Exp) { return Base.Pow(Exp); }
#undef templ
    Self Inv() { return Pow(P - 2); }
    Self &Invs() { return Pows(P - 2); }
    Self &InvEq() { return Invs(); }
    Self &InvEqual() { return Invs(); }
    friend Self Inv(Self x) { return x.Pow(P - 2); }
    friend Self operator~(Self x) { return x.Inv(); }
    friend Self operator/(Self a, Self b) { return a * ~b; }
    friend Self &operator/=(Self &a, Self b) { return a *= ~b; }
    friend Self &operator++(Self &a) { return a += 1; }
    friend Self &operator--(Self &a) { return a -= 1; }
    friend Self operator++(Self &a, int) {
        Self Tmp = a;
        return a += 1, Tmp;
    }
    friend Self operator--(Self &a, int) {
        Self Tmp = a;
        return a -= 1, Tmp;
    }
    friend Self operator+(Self a) { return a; }
    friend Self operator-(Self a) { return 0 - a; }
    bool operator==(Self a) { return x == Type(a); }
    bool operator!=(Self a) { return x != Type(a); }
};

}  // namespace Oct

#endif

const int P = 998244353;

using MInt = Oct::ModInt<int, P, long long>;

const MInt G = 3;

const int FC = 14;
const int FN = 1 << FC;

MInt w[FN << 1];
int Rev[FN];

inline void Init() {
    MInt cG = G.Pow(P - 1 >> FC), Now = w[FN] = 1;
    for (int i = FN + 1; i < FN << 1; ++i) w[i] = Now *= cG;
    for (int i = FN - 1; i; --i) w[i] = w[i << 1];
    for (int i = 1; i < FN; ++i) Rev[i] = Rev[i >> 1] >> 1 | (i & 1) << FC - 1;
}

struct GetInit { GetInit() { Init(); } } _GetInit;

inline void NTT(MInt *f, int n, bool Flag = false) {
    int Shift = FC - __builtin_ctz(n);
    for (int i = 1, x; i < n; ++i) {
        if ((x = Rev[i] >> Shift) < i) std::swap(f[x], f[i]);
    }
    for (int i = 1; i < n; i <<= 1) {
        for (int j = 0; j < n; j += i << 1) {
            for (int k = 0; k < i; ++k) {
                MInt x = f[j | k], y = f[j | i | k] * w[i << 1 | k];
                f[j | k] = x + y, f[j | i | k] = x - y;
            }
        }
    }
    if (Flag) {
        std::reverse(f + 1, f + n);
        MInt x = ~MInt(n);
        for (int i = 0; i < n; ++i) f[i] *= x;
    }
}

const int N = 3005;
const int M = N << 1;
const int K = M << 1;

int n;
int c[N], Num[N];

int fl[N], fr[N];
MInt f[N][M], t[2][FN];

MInt Ans;

inline int Tn(int n) { return 1 << 32 - __builtin_clz(n - 1); }

inline void Mul(int a, int b, int c, int Lim) {
    int na = fl[a] + fr[a] + 1, nb = fl[b] + fr[b] + 1, nc = Tn(na + nb);
    memcpy(t[0], &f[a][N - fl[a]], sizeof(MInt) * na);
    memcpy(t[1], &f[b][N - fl[b]], sizeof(MInt) * nb);
    memset(t[0] + na, 0, sizeof(MInt) * (nc - na));
    memset(t[1] + nb, 0, sizeof(MInt) * (nc - nb));
    NTT(t[0], nc), NTT(t[1], nc);
    for (int i = 0; i < nc; ++i) t[0][i] *= t[1][i];
    NTT(t[0], nc, true);
    int flc = std::min(fl[a] + fl[b], Lim);
    int frc = std::min(fr[a] + fr[b], Lim);
    memcpy(&f[c][N - flc], &t[0][fl[a] + fl[b] - flc], sizeof(MInt) * (flc + frc + 1));
    fl[c] = flc, fr[c] = frc;
}

std::vector<int> To[N];

inline void Dfs(int u, int Fa, int cs) {
    f[u][N] = 0, fl[u] = c[u] != cs, fr[u] = c[u] == cs, f[u][N + fr[u] - fl[u]] = 1;
    for (auto v : To[u]) if (v != Fa) Dfs(v, u, cs), Mul(u, v, u, Num[cs]);
    ++f[u][N];
    for (int i = 1; i <= fr[u]; ++i) Ans += f[u][N + i];
}

int main() {
    n = FastIO::Read();
    for (int i = 1; i <= n; ++i) c[i] = FastIO::Read(), ++Num[c[i]];
    for (int i = 1, x, y; i < n; ++i) {
        x = FastIO::Read(), y = FastIO::Read();
        To[x].push_back(y);
        To[y].push_back(x);
    }
    for (int i = 1; i <= n; ++i) if (Num[i]) Dfs(1, 0, i);
    std::cout << int(Ans) << '\n';
    return 0;
}