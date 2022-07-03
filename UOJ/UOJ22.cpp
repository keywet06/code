#include <bits/stdc++.h>

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
    Self &Invs() { return *this = Inv(); }
    Self &InvEq() { return Invs(); }
    Self &InvEqual() { return Invs(); }
    friend Self Inv(Self x) { return x.Inv(); }
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
};

}  // namespace Oct

#endif

using int64 = long long;

using MInt = Oct::ModInt<int, 998244353, int64>;

const int N = 5005;

bool g[N];

int n, m, x;
int a[N], b[N], c[N], s[N];

MInt Fac[N], IFa[N], f[N];

inline MInt A(int n, int m) { return Fac[n] * IFa[n - m]; }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    Fac[0] = 1;
    for (int i = 1; i < N; ++i) Fac[i] = Fac[i - 1] * i;
    IFa[N - 1] = ~Fac[N - 1];
    for (int i = N - 1; i; --i) IFa[i - 1] = IFa[i] * i;
    std::cin >> n >> x;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    std::sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i) {
        if (b[m] != a[i]) b[++m] = a[i];
        ++c[m], ++s[a[i]];
    }
    for (int i = 1; i < N; ++i) s[i] += s[i - 1];
    for (int i = 1, v; i <= m; ++i) g[v = x % b[i]] = true, f[v] += c[i] * A(n - 1, (n - 1) - s[v]);
    for (int i = b[m] - 1, j = m - 1; j; --i, j -= i < b[j]) {
        if (!g[i]) continue;
        for (int k = 1, v; k <= j; ++k) g[v = i % b[k]] = true, f[v] += c[k] * A(s[i] - 1, (s[i] - 1) - s[v]) * f[i];
    }
    for (int i = b[1] - 1; i >= 0; --i) {
        if (g[i]) return std::cout << i << std::endl << int(f[i]) << std::endl, 0;
    }
    return 0;
}