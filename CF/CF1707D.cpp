#include <bits/stdc++.h>

#define Deb std::cerr
#define Delin Deb << "[Debug] at Line " << __LINE__
#define Debug Delin << " : "
#define Deline Debug << std::endl

int P;

#ifndef OCT_MODINT_HPP
#define OCT_MODINT_HPP

namespace Oct {

template <typename Type, typename MulType = Type>
class ModInt {
   protected:
    Type x;

   public:
    using Self = ModInt<Type, MulType>;
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

using MInt = Oct::ModInt<int, long long>;

const int N = 2005;

int n;

MInt g[N], p[N], q[N], f[N][N], C[N][N];

std::vector<int> To[N];

inline void Dfs(int u, int Fa) {
    std::vector<int> T(1, 0);
    int m = 0;
    for (auto v : To[u]) if (v != Fa) Dfs(v, u), ++m, T.push_back(v);
    MInt S = 0;
    for (int i = 1; i < n; ++i) {
        p[0] = q[m + 1] = 1;
        for (int j = 1; j <= m; ++j) p[j] = p[j - 1] * f[T[j]][i];
        for (int j = m; j >= 1; --j) q[j] = q[j + 1] * f[T[j]][i];
        MInt Pi = p[m];
        if (u > 1) {
            f[u][i] = S * (MInt(0) - m), f[u][i] += S += Pi;
            for (int j = 1, v; j <= m && (v = T[j]); ++j) f[u][i] += g[v] * f[v][i], g[v] += p[j - 1] * q[j + 1];
        } else {
            f[u][i] = Pi;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> P;
    for (int i = 1, x, y; i < n; ++i) {
        std::cin >> x >> y;
        To[x].push_back(y);
        To[y].push_back(x);
    }
    Dfs(1, 1);
    for (int i = 0; i <= n; ++i) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j) C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
    for (int i = 1; i < n; ++i) {
        g[i] = f[1][i];
        for (int j = 1; j < i; ++j) g[i] -= g[j] * C[i][j];
        std::cout << int(g[i]) << " \n"[i == n - 1];
    }
    return 0;
}