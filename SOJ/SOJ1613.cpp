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

const int K = 105;
const int N = 2000005;

struct Mat {
    MInt a[K][K];
    Mat() { memset(a, 0, sizeof(a)); }
    MInt *operator[](int i) { return a[i]; }
};

inline Mat operator*(Mat a, Mat b) {
    Mat c;
    for (int i = 0; i < K; ++i) {
        for (int k = 0; k < K; ++k) {
            for (int j = 0; j < K; ++j) c[i][j] += a[i][k] * b[k][j];
        }
    }
    return c;
}

int n, k;
int a[N], Last[K];

int64 m;

MInt f[N];

Mat c, b;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> m >> k;
    f[0] = 1;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i], f[i] = Last[a[i]] ? 2 * f[i - 1] - f[Last[a[i]] - 1] : 2 * f[i - 1], Last[a[i]] = i;
    }
    std::sort(Last + 1, Last + k + 1);
    c[0][0] = f[n];
    for (int i = 1; i <= k; ++i) c[0][i] = Last[i] ? f[Last[i] - 1] : 0;
    for (int i = 1; i < k; ++i) b[i + 1][i] = 1;
    b[0][0] = 2, b[1][0] = -MInt(1), b[0][k] = 1;
    while (m) {
        if (m & 1) c = c * b;
        b = b * b, m >>= 1;
    }
    std::cout << int(c[0][0] - 1) << '\n';
    return 0;
}