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