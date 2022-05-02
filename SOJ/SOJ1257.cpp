#include <bits/stdc++.h>

using int64 = long long;

const int INF = 0x3f3f3f3f;
const int N = 2005;
const int M = 1200005;

class Edge {
   public:
    Edge *Ano, *Next;
    int To, Cost, Liu;
};

Edge e[M];
Edge *Cnt = e;
Edge *Head[N], *Cur[N];

int S, T, sum, x, n;
int a[N], b[N], Dis[N], Vis[N];

inline void Insert(int x, int y, int z, int w) {
    ++Cnt, Cnt->Next = Head[x], Head[x] = Cnt;
    Cnt->To = y, Cnt->Liu = z, Cnt->Cost = w;
}

inline void LiuInsert(int x, int y, int z, int w) {
    Insert(x, y, z, w);
    Cnt->Ano = Cnt + 1;
    Insert(y, x, 0, -w);
    Cnt->Ano = Cnt - 1;
}

inline int SPFA() {
    memset(Dis, 127, sizeof(Dis));
    std::queue<int> Que;
    Dis[S] = 0, Vis[S] = 1, Que.push(S);
    while (!Que.empty()) {
        int v = Que.front();
        Que.pop(), Vis[v] = 0;
        for (Edge *u = Head[v]; u; u = u->Next) {
            if (u->Liu && Dis[v] + u->Cost < Dis[u->To]) {
                Dis[u->To] = Dis[v] + u->Cost;
                if (!Vis[u->To]) Vis[u->To] = 1, Que.push(u->To);
            }
        }
    }
    memset(Vis, 0, sizeof(Vis));
    return Dis[T] != Dis[0];
}

int Cost;

inline int Dfs(int u, int Liu) {
    if (u == T || Liu == 0) return Liu;
    Vis[u] = 1;
    int Flow = 0, f;
    for (Edge *&e = Cur[u]; e; e = e->Next) {
        if (!e->Liu || Vis[e->To] || Dis[u] + e->Cost != Dis[e->To]) continue;
        if (!(f = Dfs(e->To, std::min(Liu - Flow, e->Liu)))) continue;
        Cost += f * e->Cost, e->Liu -= f, e->Ano->Liu += f, Flow += f;
        if (Flow == Liu) return Vis[u] = 0, Flow;
    }
    return Vis[u] = 0, Flow;
}

inline int Dinic() {
    int Ans = 0;
    while (SPFA()) memcpy(Cur, Head, sizeof(Head)), Ans += Dfs(S, INF);
    return Ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int n, m, r, t, k, c;
    std::cin >> n >> m >> r >> t >> k, c = std::min(t / r, m);
    S = 1, T = 2;
    int PA = 3, PB = PA + c + 5, PC = PB + n + 5;
    for (int i = 1; i <= c; ++i) {
        LiuInsert(S, PA + i, m, i);
        for (int j = 1; j <= n; ++j) LiuInsert(PA + i, PB + j, 1, 0);
    }
    for (int i = 1, x, y; i <= k; ++i) std::cin >> x >> y, LiuInsert(PB + x, PC + y, 1, 0);
    for (int i = 1; i <= m; ++i) LiuInsert(PC + i, T, 1, 0);
    std::vector<std::vector<int> > Pro(n + 1);
    int Ans = Dinic();
    std::cout << Ans << ' ' << int64(r) * Cost << '\n';
    for (int i = 1; i <= n; ++i) {
        int x = 0;
        for (Edge *e = Head[PB + i]; e; e = e->Next) {
            if (e->To > PC && !e->Liu) std::cout << i << ' ' << e->To - PC << ' ' << x++ * r << '\n';
        }
    }
    return 0;
}
