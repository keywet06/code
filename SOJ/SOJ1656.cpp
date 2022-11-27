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

const int N = 102;

struct Mat {
    MInt a[N][N];
    Mat() { memset(a, 0, sizeof(a)); };
    inline MInt *operator[](int i) { return a[i]; }
    inline const MInt *operator[](int i) const { return a[i]; }
};

inline Mat operator*(const Mat x, const Mat y) {
    Mat Ans;
    for (int i = 0; i < N; ++i) {
        for (int k = 0; k < N; ++k) {
            for (int j = 0; j < N; ++j) Ans[i][j] += x[i][k] * y[k][j];
        }
    }
    return Ans;
}

int n, k;

MInt p, f1[N], f2[N], *f = f1, *g = f2;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> k;
    Mat Base;
    Base[k][0] = Base[k][k + 1] = Base[k + 1][k + 1] = 1;
    for (int i = 0, a, b; i < k; ++i) {
        std::cin >> a >> b, Base[i][k + 1] = Base[i][0] = p = MInt(a) / b, Base[i][i + 1] = 1 - p;
    }
    int Now = 1;
    f[0] = 1;
    while (true) {
        if (Now & n) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) g[i] += f[j] * Base[j][i];
            }
            std::swap(f, g), memset(g, 0, sizeof(f1)), n ^= Now;
        }
        if (!n) break;
        Now <<= 1, Base = Base * Base;
    }
    std::cout << int(f[k + 1]) << '\n';
    return 0;
}