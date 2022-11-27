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

inline std::vector<int> Inv(std::vector<int> f) {
    std::vector<int> g(f.size());
    for (int i = 0; i < f.size(); ++i) g[f[i]] = i;
    return g;
}

inline std::vector<int> SA(std::vector<int> s) {
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

const int64 P = 54732537937123547;

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

using MInt = Oct::ModInt<int64, P, __int128>;

const MInt Base = 5349919, Frt = 3571999, Basr = ~Base;

const int N = 200005;

int Type[N], Left[N], Right[N];

MInt Ha1[N], Ha2[N], Po[N], *H[2] = {Ha1, Ha2};

inline MInt Hash(int c, int l, int r) { return H[c][r] - H[c][l] * Po[r - l]; }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int k, n, m;
    std::cin >> k;
    std::vector<int> aa(k);
    for (int i = 0; i < k; ++i) std::cin >> aa[i];
    std::cin >> n;
    std::vector<int> a1(n);
    for (int i = 0; i < n; ++i) std::cin >> a1[i], Ha1[i + 1] = a1[i] + Frt + Ha1[i] * Base;
    std::cin >> m;
    std::vector<int> a2(m);
    for (int i = 0; i < m; ++i) std::cin >> a2[i], Ha2[i + 1] = a2[i] + Frt + Ha2[i] * Base;
    Po[0] = 1;
    for (int i = 1; i <= n || i <= m; ++i) Po[i] = Po[i - 1] * Base;
    std::vector<int> b1 = Inv(SA(a1)), b2 = Inv(SA(a2));
    int Ans = 0;
    for (auto &x : b1) ++x;
    for (auto &x : b2) ++x;
    int lc = -1, ll = -1, tc = -1, tl = -1, i = 0, j = 0, nn[2] = {n, m};
    auto LCP = [&](int c1, int l1, int c2, int l2) -> int {
        int l = 0, r = std::min(nn[c1] - l1 + 1, nn[c2] - l2 + 1);
        while (l < r) {
            int m = l + r + 1 >> 1;
            if (Hash(c1, l1 - 1, l1 + m - 1) == Hash(c2, l2 - 1, l2 + m - 1)) {
                l = m;
            } else {
                r = m - 1;
            }
        }
        return l;
    };
    auto Next = [&](int c, int l) -> void {
        if (tc == -1) return tc = c, tl = l, void(0);
        lc = tc, ll = tl, tc = c, tl = l;
        Ans = std::max(Ans, LCP(lc, ll, tc, tl));
    };
    while (i < n && j < m) {
        int x = LCP(0, b1[i], 1, b2[j]);
        if ((b2[j] + x <= m) && (b1[i] + x == n + 1 || a1[b1[i] + x - 1] < a2[b2[j] + x - 1])) {
            Next(0, b1[i++]);
        } else {
            Next(1, b2[j++]);
        }
    }
    while (i < n) Next(0, b1[i++]);
    while (j < m) Next(1, b2[j++]);
    if (Ans > 0) return std::cout << n - Ans + m - Ans << '\n', 0;
    memset(Left, 50, sizeof(Left));
    memset(Right, 0, sizeof(Right));
    for (auto x : a1) Type[x] = 1;
    for (int i = 0; i < m; ++i) {
        Type[a2[i]] = 2, Left[a2[i]] = std::min(Left[a2[i]], i), Right[a2[i]] = std::max(Right[a2[i]], i);
    }
    Ans = INT_MAX;
    int l1 = -1e8, l2 = -1e8;
    for (int i = 0; i < k; ++i) {
        if (Type[aa[i]] == 1) {
            Ans = std::min(Ans, n - 1 + i - l2 + i - l2 + m - 1), l1 = i;
        } else if (Type[aa[i]] == 2) {
            Ans = std::min(Ans, n - 1 + i - l1 + i - l1 + m - 1), l2 = i;
        }
    }
    std::cout << Ans << '\n';
    return 0;
}