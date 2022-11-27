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

using MInt = Oct::ModInt<long long, 71730605914435529, __int128>;
const int Base = 14327;
const int Add = 1181;

const int C = 128;
const int N = 100005;

char Rev[C];

int n;

MInt Po[N], Has[N], Har[N];

std::string s;

inline void Print(int l, int r) {
    for (int i = 1; i < l; ++i) std::cout << s[i];
    for (int i = r; i >= l; --i) std::cout << Rev[s[i]];
    for (int i = r + 1; i <= n; ++i) std::cout << s[i];
    std::cout << '\n';
}

inline MInt Hs(int l, int r) { return Has[r] - Has[l - 1] * Po[r - l + 1]; }
inline MInt Hr(int l, int r) { return Har[r] - Har[l + 1] * Po[l - r + 1]; }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    Rev['A'] = 'T', Rev['T'] = 'A', Rev['C'] = 'G', Rev['G'] = 'C';
    std::cin >> s, n = s.length(), s = ' ' + s + ' ';
    char MinRev = 'a', R = 'a';
    int p = 0;
    for (int i = n; i >= 1; --i) {
        if ((MinRev = std::min(MinRev, Rev[s[i]])) < s[i]) p = i, R = MinRev;
    }
    if (p == 0) {
        for (int i = 1; i < n; ++i) {
            if (s[i] == Rev[s[i + 1]]) return Print(i, i + 1), 0;
        }
        return Print(n, n), 0;
    }
    Po[0] = 1;
    for (int i = 1; i <= n; ++i) Po[i] = Po[i - 1] * Base;
    for (int i = 1; i <= n; ++i) Has[i] = Has[i - 1] * Base + s[i] + Add;
    for (int i = n; i; --i) Har[i] = Har[i + 1] * Base + Rev[s[i]] + Add;
    int u = 0;
    for (int v = p; v <= n; ++v) {
        if (Rev[s[v]] != R || !u && (u = v)) continue;
        int ul1 = u, ur1 = p, ul2 = u + 1, ur2 = v;
        int vl1 = v, vr1 = v - u + p, vl2 = vr1 - 1, vr2 = p;
        if (Hr(ul1, ur1) != Hr(vl1, vr1)) {
            int l = 0, r = ul1 - ur1;
            while (l < r) {
                int Mid = l + r >> 1;
                Hr(ul1, ul1 - Mid) != Hr(vl1, vl1 - Mid) ? r = Mid : l = Mid + 1;
            }
            if (Rev[s[vl1 - l]] < Rev[s[ul1 - l]]) u = v;
        } else if (Hs(ul2, ur2) != Hr(vl2, vr2)) {
            int l = 0, r = ur2 - ul2;
            while (l < r) {
                int Mid = l + r >> 1;
                Hs(ul2, ul2 + Mid) != Hr(vl2, vl2 - Mid) ? r = Mid : l = Mid + 1;
            }
            if (Rev[s[vl2 - l]] < s[ul2 + l]) u = v;
        }
    }
    return Print(p, u), 0;
}