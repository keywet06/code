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

const MInt R2 = ~MInt(2);

const int N = 100005;
const int C = 30;

int n, m;
int Num[C];

std::vector<int> Val[N];

MInt Ans;
MInt Pre[N], Re[N];

inline MInt Bi(int m, int n) { return Pre[m] * Re[n] * Re[m - n]; }
inline MInt P2(int x) { return MInt((1ll << x) % P); }
inline MInt Solve(int n, int c) {
    return (c & 1 ? R2 * (n + 1) * Bi(n, c) : R2 * (n * Bi(n + 1, c + 1) - (n + 1) * Bi(n, c + 1))) * Pre[c] *
           Pre[n - c];
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> m;
    Pre[0] = 1;
    for (int i = 1; i <= m + 1; ++i) Pre[i] = Pre[i - 1] * i;
    Re[m + 1] = ~Pre[m + 1];
    for (int i = m; i >= 0; --i) Re[i] = Re[i + 1] * (i + 1);
    for (int i = 1, u, v, w; i <= m; ++i) {
        std::cin >> u >> v >> w;
        Val[u].push_back(w);
        Val[v].push_back(w);
    }
    for (int u = 1; u <= n; ++u) {
        memset(Num, 0, sizeof(Num));
        for (auto w : Val[u]) {
            for (int i = 0; i < C; ++i) Num[i] += w >> i & 1;
        }
        for (int i = 0; i < C; ++i) Ans += P2(i) * Solve(m, Num[i]);
    }
    std::cout << int(Ans) << std::endl;
    return 0;
}