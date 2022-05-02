#include <bits/stdc++.h>

#define Deb std::cerr
#define Delin Deb << "[Debug] at Line " << __LINE__
#define Debug Delin << " : "
#define Deline Delin << std::endl

#ifndef OCT_MODINT_HPP
#define OCT_MODINT_HPP

namespace Oct {

template <typename DataType, DataType P, typename MulType>
class ModInt {
   protected:
    DataType x;

   public:
    using Self = ModInt<DataType, P, MulType>;
    ModInt() : x(0) {}
    ModInt(DataType c) : x(c < 0 ? (c % P + P) % P : (c >= P ? c % P : c)) {}
    explicit operator DataType() { return x; }
    DataType &Data() { return x; }
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

using int64 = long long;
using MInt = Oct::ModInt<int, 998244353, int64>;

std::mt19937_64 Rand(std::chrono::system_clock::now().time_since_epoch().count());

int64 Random(int64 x) { return Rand() % x; }
int64 Random(int64 l, int64 r) { return Random(r - l + 1) + l; }

const int N = 600005;
const int C = 40;
const int D = 80;
const int E = D * D;

int n, k;
int fn[N], gn[N], tn[E];
int f[N][C], g[N][D], t[E][D];

MInt Ans;
MInt dp[N], Mu[D];

std::vector<int> To[N];

inline void Adds(int &an, int *a, int bn, int *b, int Up) {
    for (int i = an + 1; i <= bn + Up; ++i) a[i] = 0;
    for (int i = 0; i <= bn; ++i) a[i + Up] += b[i];
    if (bn + Up > an) an = bn + Up;
}

inline void Add(int an, int *a, int bn, int *b, int &cn, int *c, int Up) {
    memcpy(c, a, sizeof(int) * ((cn = an) + 1));
    Adds(cn, c, bn, b, Up);
}

inline void Dfs1(int u, int Fa) {
    f[u][0] = 1;
    for (int v : To[u]) {
        if (v == Fa) continue;
        Dfs1(v, u);
        Adds(fn[u], f[u], fn[v], f[v], 1);
    }
}

inline void Dfs2(int u, int Fa) {
    for (int l = 1; l <= n; ++l) {
        if (!int(Mu[l])) continue;
        int Num = gn[u] >= l;
        for (int v : To[u]) {
            if (v != Fa) Num += fn[v] + 1 >= l;
        }
        if (Num < k) break;
        memset(dp, 0, sizeof(MInt) * (k + 1));
        dp[0] = 1;
        for (int v : To[u]) {
            int x = 0;
            if (v != Fa) {
                if (fn[v] + 1 < l) continue;
                for (int i = l - 1; i <= fn[v]; i += l) x += f[v][i];
            } else {
                if (gn[u] < l) continue;
                for (int i = l; i <= gn[u]; i += l) x += g[u][i];
            }
            for (int i = k; i; --i) dp[i] += dp[i - 1] * x;
        }
        Ans += dp[k] * Mu[l];
    }
    std::vector<int> Ts;
    for (int v : To[u]) {
        if (v != Fa) Ts.push_back(v);
    }
    int n = Ts.size();
    if (!n) return;
    t[n - 1][0] = 0;
    memcpy(t[n - 1] + 1, g[u], tn[n - 1] = gn[u] + 1);
    for (int i = n - 2; i >= 0; --i) {
        Add(tn[i + 1], t[i + 1], fn[Ts[i + 1]], f[Ts[i + 1]], tn[i], t[i], 2);
    }
    tn[n] = 1, t[n][0] = 0, t[n][1] = 1;
    for (int i = 0; i < n; ++i) {
        Add(tn[n], t[n], tn[i], t[i], gn[Ts[i]], g[Ts[i]], 0);
        if (i == n - 1) break;
        Adds(tn[n], t[n], fn[Ts[i]], f[Ts[i]], 2);
    }
    for (int i = 0; i < n; ++i) Dfs2(Ts[i], u);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    Mu[1] = 1;
    for (int i = 2; i < D; ++i) {
        for (int j = 2; j <= i; ++j) {
            if (i % j) continue;
            if (i / j % j) Mu[i] = -Mu[i / j];
            break;
        }
    }
    std::cin >> n >> k;
    for (int i = 1, x, y; i < n; ++i) {
        std::cin >> x >> y;
        To[x].push_back(y);
        To[y].push_back(x);
    }
    Dfs1(1, 1), Dfs2(1, 1);
    std::cout << int(Ans) << std::endl;
    return 0;
}