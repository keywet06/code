#include <bits/stdc++.h>

using int32 = int;
using int64 = long long;

inline int BiFfs(int32 x) { return __builtin_ffs(x); }
inline int BiClz(int32 x) { return __builtin_clz(x); }
inline int BiCtz(int32 x) { return __builtin_ctz(x); }
inline int BiPop(int32 x) { return __builtin_popcount(x); }
inline int BiPar(int32 x) { return __builtin_parity(x); }
inline int BiFfs(int64 x) { return __builtin_ffsll(x); }
inline int BiClz(int64 x) { return __builtin_clzll(x); }
inline int BiCtz(int64 x) { return __builtin_ctzll(x); }
inline int BiPop(int64 x) { return __builtin_popcountll(x); }
inline int BiPar(int64 x) { return __builtin_parityll(x); }

const int P = 998244353;

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
    templ Self Pow(ExpType Exp) {
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

inline std::vector<int> Inv(std::vector<int> f) {
    std::vector<int> g(f.size());
    for (int i = 0; i < f.size(); ++i) g[f[i]] = i;
    return g;
}

inline std::vector<int> SA(std::string s) {
    int n = s.size(), m = 32 - BiClz(n - 1);
    std::vector<int> f(n), g(n);
    int T = 0;
    [&]() {
        std::vector<int> Id(n);
        for (int i = 0; i < n; ++i) Id[i] = i;
        std::stable_sort(Id.begin(), Id.end(), [&](int x, int y) { return s[x] < s[y]; });
        f[Id[0]] = ++T;
        for (int i = 1; i < n; ++i) f[Id[i]] = T += s[Id[i]] != s[Id[i - 1]];
    }();
    for (int i = 0, I = 1, c = 1; i < m; ++i, ++I, c <<= 1) {
        std::vector<std::vector<int> > So1(T + 1), So2(T + 1);
        auto Sub = [&](int j) { return j + c < n ? f[j + c] : 0; };
        for (int j = 0; j < n; ++j) So1[Sub(j)].push_back(j);
        for (auto v : So1) {
            for (int x : v) So2[f[x]].push_back(x);
        }
        T = 0;
        for (auto v : So2) {
            for (int j = 0; j < v.size(); ++j) g[v[j]] = T += !j || Sub(v[j - 1]) != Sub(v[j]);
        }
        f.swap(g);
        if (T == n) break;
    }
    for (int &x : f) --x;
    return f;
}

template <typename Type, typename Oper>
class ST {
    
    std::vector<std::vector<Type> > St;
    ST(std::vector<Type> a) {
        int n = a.size(), m = 31 - BiClz(n);
        St.resize(m + 1), St[0] = a;
        for (int I = 0, i = 1, c = 1; i <= m; ++I, ++i, c <<= 1) {
            int T = n - (c << 1);
            St[i].resize(T);
            for (int j = 0; j < T; ++j) St[i][j] = Oper()(St[I][j], St[I][j + c]);
        }
    }
    inline Type Query(int l, int r) {
        int x = 31 - BiClz(r - l + 1);
        return Oper()(St[x][l], St[x][r - (1 << x) + 1]);
    }
};

const int Be = 37, Pe = 101, Re = Inv(Pe);

class LCPs {

    inline std::vector<int> Solve(std::string s) {
        int n = s.size();
        auto Sa = SA(s), So = Inv(Sa);
        std::vector<int> Ha(n), Pp(n + 1), Pr(n + 1);
        Ha[0] = s[0] - 'a' + Be, Pp[0] = Pr[0] = 1;
        for (int i = 1; i < n; ++i) Ha[i] = Add(Mul(Ha[i - 1], Pe), s[i] - 'a' + Be);
        for (int i = 1; i <= n; ++i) Pp[i] = Mul(Pp[i - 1], Pe);
        for (int i = 1; i <= n; ++i) Pr[i] = Mul(Pr[i - 1], Re);
        auto Hash = [&](int l, int r) -> int { return Sub(Ha[r], l ? Mul(Pr[r - l + 1], Ha[l - 1]) : 0); };
        std::vector<int> Com(n - 1);
        for (int i = 0, I = 1; I < n; ++I) {
            int a = So[i], b = So[I], l = 0, r = n - std::max(a, b), Mid;
            while (l < r) Mid = l + r + 1 >> 1, Hash(a, a + Mid - 1) == Hash(b, b + Mid - 1) ? l = Mid : r = Mid - 1;
            Com[i] = l;
        }
        return Com;
    }
};

inline std::string Inv(std::string s) {
    std::string Res;
    int n = s.size();
    Res.resize(n);
    for (int i = 0, j = n - 1; i < n; ++i, --j) Res[i] = s[j];
    return Res;
}

int Solve() {
    std::string s;
    std::cin >> s;
    return 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int T;
    std::cin >> T;
    while (T--) Solve();
    return 0;
}