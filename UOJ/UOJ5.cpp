#include <bits/stdc++.h>

#ifndef OCT_MODINT_HPP
#define OCT_MODINT_HPP

namespace Oct {

template <typename Type, Type P, typename MulType>
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
    templ friend Self Pow(Self Base, ExpType Exp) {
        Self Ret(1);
        while (Exp) {
            if (Exp & 1) Ret *= Base;
            Base *= Base, Exp >>= 1;
        }
        return Ret;
    }
    templ Self Pow(ExpType Exp) { return Pow(*this, Exp); }
    templ Self &Pows(ExpType Exp) { return *this = Pow(*this, Exp); }
    templ Self &PowEq(ExpType Exp) { return Pows(Exp); }
    templ Self &PowEqual(ExpType Exp) { return Pows(Exp); }
#undef templ
    friend Self Inv(Self x) { return Pow(x, P - 2); }
    friend Self operator~(Self x) { return Inv(x); }
    Self Inv() { return ~*this; }
    Self &Invs() { return *this = ~*this; }
    Self &InvEq() { return Invs(); }
    Self &InvEqual() { return Invs(); }
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

using MInt = Oct::ModInt<int, 1000000007, long long>;

const int N = int(1e6) + 5;

int T, n, Fail[N], Num[N];

std::string s;


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> T;
    while (T--) {
        std::cin >> s, n = s.length(), s = ' ' + s;
        MInt Ans = 1;
        Num[0] = -1;
        for (int i = 2; i <= n; ++i) {
            int &j = Fail[i] = Fail[i - 1];
            while (j && s[j + 1] != s[i]) j = Fail[j];
            int t = Num[i] = Num[j += s[j + 1] == s[i]] + 1;
            if (j << 1 > i) t -= (j - (i >> 1) - 1) / (i - j) + 1;
            Ans *= t + 1;
        }
        std::cout << int(Ans) << std::endl;
    }
    return 0;
}