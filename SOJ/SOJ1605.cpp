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

using int64 = long long;

const int P = 1000000007;

using MInt = Oct::ModInt<int, P, int64>;

const int N = 605;
const int M = N << 1;

int n, Lef, Nef;
int Left[M];

MInt g[N], f[M][N], C[M][M];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n;
    for (int i = 1, x; i <= n; ++i) std::cin >> x, Left[x] = 1;
    for (int i = 0; i < M; ++i) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j) C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
    g[0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) g[i] += g[j] * g[i - j - 1] * C[i - 1][j] * (j + 2);
    }
    f[n << 1 | 1][0] = 1;
    for (int i = n << 1; i; --i) {
        if (!Left[i]) {
            for (int j = Nef + 1; j <= Lef; ++j) f[i][j] = f[i + 1][j] * (j - Nef);
            ++Nef;
        } else {
            for (int j = Nef; j <= Lef + 1; ++j) {
                f[i][j] = f[i + 1][j];
                for (int k = 1; j - k >= Nef; ++k) {
                    f[i][j] += f[i + 1][j - k] * C[Lef - j + k][k - 1] * g[k - 1] * (k + 1);
                }
            }
            ++Lef;
        }
    }
    std::cout << int(f[1][n] * (~MInt(2)).Pow(n)) << std::endl;
    return 0;
}