#pragma GCC optimize("Ofast")

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
    bool operator==(Self a) { return x == int(a); }
};

}  // namespace Oct

#endif

const int P = 998244353;

using MInt = Oct::ModInt<int, P, long long>;

const int N = 105;

int n;
int a[N], p[N];

MInt f[N][N][N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> a[i], p[i] = i;
    std::sort(p + 1, p + n + 1, [](int x, int y) { return a[x] == a[y] ? x < y : a[x] < a[y]; });
    for (int i = 1; i <= n; ++i) a[p[i]] = i;
    for (int l = 1; l <= n + 1; ++l) {
        for (int r = 1; r <= n; ++r) {
            for (int c = 1; c <= n; ++c) f[l][r][c] = l >= r || c == 1 ? 1 : 0;
        }
    }
    for (int len = 1; len < n; ++len) {
        for (int l = 1, r = l + len; (r = l + len) <= n; ++l) {
            for (int c = 2; c <= n; ++c) {
                int p = 0;
                MInt &x = f[l][r][c];
                for (int i = l; i <= r; ++i) if (a[i] == c && (p = i, true)) break;
                if (!p && (x = f[l][r][c - 1], true)) continue;
                for (int i = p; i <= r; ++i) if (a[i] <= c) x += f[l][i][c - 1] * f[i + 1][r][c];
            }
        }
    }
    std::cout << int(f[1][n][n]) << std::endl;
    return 0;
}