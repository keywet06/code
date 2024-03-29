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

using MInt = Oct::ModInt<int, 998244353, long long>;

const int N = 505;

struct Dp {
    int n;
    MInt f[N], g[N];
    Dp() : n(0) { f[0] = 1; }
    void Add(int x) {
        for (int i = n++; i >= 0; --i) f[i + 1] += f[i], g[i + 1] += g[i] + f[i] * x;
    }
    void Sub(int x) {
        for (int i = 1; i <= n; ++i) f[i - 1] += f[i] * i, g[i - 1] += g[i] * i + f[i] * i * x;
    }
};

int n;

Dp Col[N], Row[N];

std::string Map[N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n;
    for (int i = 0; i < n; ++i) std::cin >> Map[i];
    for (int i = 0, x; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> x;
            if (Map[i][j] == 'U') Col[j].Sub(x);
            if (Map[i][j] == 'D') Col[j].Add(x);
            if (Map[i][j] == 'L') Row[i].Sub(x);
            if (Map[i][j] == 'R') Row[i].Add(x);
        }
    }
    MInt Sum = 0, Mul = 1;
    for (int i = 0; i < n; ++i) Sum += Row[i].g[0] / Row[i].f[0], Mul *= Row[i].f[0];
    for (int i = 0; i < n; ++i) Sum += Col[i].g[0] / Col[i].f[0], Mul *= Col[i].f[0];
    std::cout << int(Sum * Mul) << '\n';
    return 0;
}