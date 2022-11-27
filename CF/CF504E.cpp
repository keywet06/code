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
    bool operator!=(Self a) { return x != int(a); }
};

}  // namespace Oct

#endif

#define Deb std::cerr
#define Delin Deb << "[Debug] at Line " << __LINE__
#define Debug Delin << " : "
#define Deline Debug << std::endl

#define CTZ __builtin_ctz
#define PB push_back

const int P = 1000100009, E = 4816657, D = 449;
using MI = Oct::ModInt<int, P, long long>;
const MI F = ~MI(E);

const int N = 1000005, C = 20;

int n, q, Dep[N], Fa[N][C];
MI s[N], H1[N], H2[N], Fc[N], Fr[N];
std::vector<int> To[N];
std::string ts;

inline void Dfs1(int u, int f) {
    Debug << "Dfs1(" << u << ", " << f << ")" << std::endl;
    Fa[u][0] = f, H2[u] = H2[f] * E + s[u], H1[u] = Fc[Dep[u] = Dep[f] + 1] * s[u] + H1[f];
    for (int i = 1; i < C; ++i) Fa[u][i] = Fa[Fa[u][i - 1]][i - 1];
    for (auto v : To[u])
        if (v != f) Dfs1(v, u);
}

inline MI utd(int u, int v) { return (H1[v] - H1[u]) * Fr[Dep[u] + 1]; }
inline MI dtu(int u, int v) { return H2[u] - H2[v] * Fc[Dep[u] - Dep[v]]; }
inline int Up(int u, int x) {
    while (x) u = Fa[u][CTZ(x)], x &= x - 1;
    return u;
}
inline int d(int u, int v) { return Dep[u] - Dep[v]; }
inline int lca(int u, int v) {
    Debug << "lca(" << u << ", " << v << ") = ";
    if (Dep[u] < Dep[v]) std::swap(u, v);
    u = Up(u, Dep[u] - Dep[v]);
    if (u == v) return Deb << u << std::endl, u;
    for (int i = C - 1; i >= 0; --i)
        if (Fa[u][i] != Fa[v][i]) u = Fa[u][i], v = Fa[v][i];
    return Deb << Fa[u][0] << std::endl, Fa[u][0];
}
inline int uutdd(int u1, int v1, int u2, int v2) {
    Debug << "uutdd( (" << u1 << " => " << v1 << "] & (" << u2 << " => " << v2 << "] )" << std::endl;
    d(v1, u1) < d(v2, u2) ? v2 = Up(v2, d(v2, u2) - d(v1, u1)) : v1 = Up(v1, d(v1, u1) - d(v2, u2));
    Debug << "uutdd( (" << u1 << " => " << v1 << "] & (" << u2 << " => " << v2 << "] )" << std::endl;
    if (utd(u1, v1) == utd(u2, v2)) return d(v1, u1);
    for (int i = C - 1; i >= 0; --i)
        if (1 << i <= d(v1, u1) && utd(u1, Fa[v1][i]) != utd(u2, Fa[v2][i])) 
        Debug << "utd(" << u1 << ", " << Fa[v1][i] << ") != utd(" << u2 << ", " << Fa[v2][i] << ")" << std::endl, 
        v1 = Fa[v1][i], v2 = Fa[v2][i];
    return d(v1, u1) - 1;
}
inline int ddtuu(int u1, int v1, int u2, int v2) {
    Debug << "ddtuu( [" << u1 << " => " << v1 << ") & [" << u2 << " => " << v2 << ") )" << std::endl;
    if (d(u1, v1) > d(u2, v2)) std::swap(u1, u2), std::swap(v1, v2);
    int f1 = u1;
    for (int i = C - 1; i >= 0; --i)
        if (1 << i <= d(u1, v1) && dtu(u1, Fa[u1][i]) == utd(u2, Fa[u2][i])) u1 = Fa[u1][i], u2 = Fa[u2][i];
    return d(f1, u1);
}
int p1[30], p2[30];
inline int udtdu(int u1, int v1, int u2, int v2) {
    Debug << "udtdu( (" << u1 << " => " << v1 << "] & [" << u2 << " => " << v2 << ") )" << std::endl;
    int t = d(v1, u1) - d(u2, v2);
    t < 0 ? v2 = Up(u2, d(v1, u1)) : v1 = Up(v1, t);
    int x = d(v1, u1), n = __builtin_popcount(x);
    if (!x) return 0;
    p1[0] = u1, p1[n] = v1, p2[0] = u2, p2[n] = v2;
    for (int i = 1; i < n; ++i) p2[i] = Fa[p2[i - 1]][CTZ(x)], x &= x - 1;
    for (int i = n - 1; i; --i) p1[i] = Fa[p1[i + 1]][CTZ(d(p2[i], p2[i + 1]))];
    for (int i = 1; i <= n; ++i) assert(d(p1[i], p1[i - 1]) == d(p2[i - 1], p2[i]));
    Debug << "p1 =";
    for (int i = 0; i <= n; ++i) Deb << ' ' << p1[i];
    Deb << std::endl;
    Debug << "p2 =";
    for (int i = 0; i <= n; ++i) Deb << ' ' << p2[i];
    Deb << std::endl;
    for (int i = 1; i <= n; ++i) {
        int t = u1, u1 = p1[i - 1], v1 = p1[i], u2 = p2[i - 1], v2 = p2[i];
        if (utd(u1, v1) == dtu(u2, v2)) continue;
        Debug << "utd(" << u1 << ", " << v1 << ") != dtu(" << u2 << ", " << v2 << ")" << std::endl;
        for (int j = CTZ(d(v1, u1)) - 1; j >= 0; --j) {
            if (utd(u1, Fa[v1][j]) == dtu(u2, Fa[u2][j])) {
                u1 = Fa[v1][j], u2 = Fa[u2][j];
            } else {
                v1 = Fa[v1][j], v2 = Fa[u2][j];
            }
        }
        return Debug << "Type1: returns " << d(u1, t) << std::endl, d(u1, t);
    }
    return Debug << "Type2: returns " << d(v1, u1) << std::endl, d(v1, u1);
}

int main() {
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> ts, Fc[0] = Fr[0] = 1, Dep[0] = -1;
    for (int i = 0; i < n; ++i) s[i + 1] = ts[i] + D, Fc[i + 1] = Fc[i] * E, Fr[i + 1] = Fr[i] * F;
    for (int i = 1, x, y; i < n; ++i) std::cin >> x >> y, To[x].PB(y), To[y].PB(x);
    Dfs1(1, 0);
    std::cin >> q;
    while (q--) {
        int u1, v1, u2, v2;
        std::cin >> u1 >> v1 >> u2 >> v2;
        Debug << "GetQuery " << u1 << " => " << v1 << "  &  " << u2 << " => " << v2 << std::endl;
        int o1 = lca(u1, v1), o2 = lca(u2, v2);
        if (d(u1, o1) > d(u2, o2)) std::swap(u1, u2), std::swap(v1, v2), std::swap(o1, o2);
        int Ans = 0, Now;
        Ans += Now = ddtuu(u1, o1, u2, o2);
        if (Now < d(u1, o1) && (std::cout << Ans << '\n', true)) continue;
        Debug << "Ans1 = " << Ans << std::endl;
        u2 = Up(u2, Now);
        Ans += Now = udtdu(Fa[o1][0], v1, u2, o2);
        if (Now < std::min(d(v1, Fa[o1][0]), d(u2, o2)) && (std::cout << Ans << '\n', true)) continue;
        Debug << "Ans2 = " << Ans << std::endl;
        u1 = Up(v1, d(v1, Fa[o1][0]) - Now);
        std::cout << (Ans += uutdd(u1, v1, Fa[o2][0], v2)) << '\n';
    }
    return 0;
}