#include <bits/stdc++.h>

using int64 = long long;
using p65 = std::pair<int64, int>;

struct Edge {
    int v;
    int64 Val;
    Edge() {}
    Edge(int Cv, int64 CVal) : v(Cv), Val(CVal) {}
};

const int C = 20;
const int N = 100005;
const int64 MaxV = int64(N) * 1000005;

int n, q, Id1, Id2, Ids, Ban1, Ban2, Spl;
int Fa[N][C];

int64 x, y, z, Max = -1, Sum, Sig, SLeft, SRight, L;
int64 Deep[N], f[N];
int64 Dis[N][C];

std::vector<int> Dia;
std::vector<int64> DVal;
std::vector<Edge> To[N];

std::stack<int64> Sta;

inline p65 Dfs1(int u, int f) {
    p65 Max1(0, u), Max2(0, u), Res;
    Fa[u][0] = f;
    for (Edge &e : To[u]) {
        if (e.v == f) continue;
        Dis[e.v][0] = e.Val;
        Res = Dfs1(e.v, u), Res.first += e.Val;
        if (Res > Max1) {
            Max2 = Max1, Max1 = Res;
        } else if (Res > Max2) {
            Max2 = Res;
        }
    }
    if (Max1.first + Max2.first > Max) {
        Max = Max1.first + Max2.first;
        Id1 = Max1.second, Id2 = Max2.second, Ids = u;
    }
    return Max1;
}

inline bool Check(int u, int v) {
    return (u != Ban1 || v != Ban2) && (u != Ban2 || v != Ban1);
}

inline void Dfs2(int u, int fa, int64 Val) {
    Fa[u][0] = fa, Dis[u][0] = Val;
    for (int i = 1; i < C; ++i) {
        Fa[u][i] = Fa[Fa[u][i - 1]][i - 1];
        Dis[u][i] = Dis[u][i - 1] + Dis[Fa[u][i - 1]][i - 1];
    }
    int64 &F = f[u];
    for (Edge e : To[u]) {
        if (e.v != fa || !Check(e.v, u)) continue;
        Dfs2(e.v, u, e.Val);
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i < n; ++i) {
        std::cin >> x >> y >> z;
        To[x].emplace_back(y, z);
        To[y].emplace_back(x, z);
    }
    Dfs1(1, 0);
    for (int u = Id1; u != Ids; u = Fa[u][0]) {
        Dia.push_back(u), DVal.push_back(Dis[u][0]);
    }
    Dia.push_back(Ids);
    for (int u = Id2; u != Ids; u = Fa[u][0]) Sta.push(u);
    while (!Sta.empty()) Dia.push_back(Sta.top()), Sta.pop();
    for (int u = Id2; u != Ids; u = Fa[u][0]) Sta.push(Dis[u][0]);
    while (!Sta.empty()) DVal.push_back(Sta.top()), Sta.pop();
    for (int64 &Val : DVal) Sum += Val;
    for (int i = 0; i < DVal.size(); ++i) {
        if ((Sig += DVal[i]) * 2 > Sum) {
            SLeft = Sig, SRight = Sum - Sig + DVal[i];
            Ban1 = Dia[i], Ban2 = Dia[i + 1];
            break;
        }
    }
    Dfs2(Dia.front(), 0, MaxV);
    Dfs2(Dia.back(), 0, MaxV);
    std::cin >> q;
    while (q--) {
        std::cin >> L;
        
    }
    return 0;
}