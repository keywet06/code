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

const int N = 55;
const int M = N * N;

int n, m;
int Dis[N], Inq[N];

std::vector<int> Son[N];

std::vector<std::pair<int, int> > To[N];

std::queue<int> Que;

inline void SPFA() {
    memset(Dis, 63, sizeof(Dis));
    Que.push(1), Inq[1] = true;
    while (!Que.empty()) {
        int u = Que.front();
        Inq[u] = false;
        for (auto p : To[u]) {
            int v = p.first, l = p.second;
            if (Dis[u] + l < Dis[v]) {
                Dis[v] = Dis[v] + l;
                if (!Inq[v]) Que.push(v), Inq[v] = true;
            }
        }
    }
}

int Size[N], Bize[N];

MInt Inv[N];
MInt f[N][N], g[N][N][N][N];

inline void Dfs(int u) {
    if (Son[u].empty()) {
        Size[u] = Bize[u] = 1;
        for (int i = 1; i <= n; ++i) g[u][i][1][0] = g[i][1][0][1] = f[u][i] = 1;
        return;
    }
    for (int i = 1; i <= n; ++i) g[u][i][0][0] = 1;
    for (auto v : Son[u]) {
        Dfs(v);
        Size[u] += Size[v], Bize[u] += Bize[v];
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> m;
    Inv[0] = Inv[1] = 1;
    for (int i = 2; i <= n; ++i) Inv[i] = -MInt(P / i) * Inv[P % i];
    for (int i = 1, x, y, w; i <= m; ++i) std::cin >> x >> y >> w, To[x].emplace_back(y, w);
    SPFA();
    for (int u = 1; u <= n; ++u) {
        for (auto p : To[u]) {
            if (Dis[u] + p.second == Dis[p.second]) Son[u].push_back(p.second);
        }
    }
    Dfs(1);
    MInt Ans = 0;
    for (int i = 1; i <= n; ++i) Ans += (f[1][i] - f[1][i - 1]) * i;
    std::cout << int(Ans) << std::endl;
    return 0;
}
