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
    bool operator==(Self a) { return x == int(a); }
};

}  // namespace Oct

#endif

const int N = 100005;

int n;

std::string s;

int f1[N], f2[N], t[N], *f = f1, *g = f2;
int MaxR = 26, Top, sy[N], Head[N], Next[N], Id[N];

inline void Clear() { Top = 0, memset(Head, 0, sizeof(int) * (MaxR + 1)); }
inline void Add(int i, int x) { Next[++Top] = Head[i], Head[i] = Top, Id[Top] = x; }

int Ans[N];

using MInt = Oct::ModInt<int, 347138959, long long>;

const MInt Mu = 59;
const MInt Pl = 17;

MInt H[N], Po[N];

inline MInt Hash(int l, int r) { return --l >= 0 ? H[r] - H[l] * Po[r - l] : H[r]; }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> s, n = s.length();
    for (int i = 0; i < n; ++i) f[i] = s[i] - 'a' + 1;
    for (int d = 1; d <= n; d <<= 1) {
        for (int i = 0; i < n; ++i) Add(sy[i] = i + d < n ? f[i + d] : 0, i);
        for (int i = MaxR; i >= 0; --i) {
            for (int e = Head[i]; e; e = Next[e]) t[--Top] = Id[e];
        }
        Clear();
        for (int i = 0; i < n; ++i) Add(f[t[i]], t[i]);
        for (int i = MaxR; i >= 0; --i) {
            for (int e = Head[i]; e; e = Next[e]) t[--Top] = Id[e];
        }
        Clear();
        g[t[0]] = MaxR = 1;
        for (int i = 1; i < n; ++i) g[t[i]] = MaxR += f[t[i]] != f[t[i - 1]] || sy[t[i]] != sy[t[i - 1]];
        std::swap(f, g);
    }
    for (int i = 0; i < n; ++i) Ans[f[i]] = i + 1;
    for (int i = 1; i <= n; ++i) std::cout << Ans[i] << " \n"[i == n];
    for (int i = int(Po[0] = 1); i <= n; ++i) Po[i] = Po[i - 1] * Mu;
    for (int i = 0; i < n; ++i) H[i] = s[i] - 'a' + Pl;
    for (int i = 1; i < n; ++i) H[i] += H[i - 1] * Mu;
    for (int i = 1, j = 2; j <= n; ++i, ++j) {
        int l1 = Ans[i] - 1, l2 = Ans[j] - 1;
        int l = 0, r = n - std::max(l1, l2);
        while (l < r) {
            int Mid = l + r + 1 >> 1;
            if (Hash(l1, l1 + Mid - 1) == Hash(l2, l2 + Mid - 1)) {
                l = Mid;
            } else {
                r = Mid - 1;
            }
        }
        std::cout << l << " \n"[j == n];
    }
    return 0;
}