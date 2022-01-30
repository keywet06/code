#include <bits/stdc++.h>

const int N = 100005;
const int M = 500005;

struct edge {
    int u, v, Use;
    int Next(int x) { return u + v - x; }
};

struct point {
    int u, S;
    point *Next;
};

int n, m, x, y, Last;
int Deg[N], In[N];

edge Edge[M];
edge *ETop = Edge;

point Point[M];
point *PTop = Point;
point *Po[N];

std::stack<edge *> To[N];

inline void AddEdge(int u, int v) {
    ++ETop, ETop->u = u, ETop->v = v, ETop->Use = 0;
    To[u].push(ETop), To[v].push(ETop);
    ++Deg[u], ++Deg[v];
}

inline point *NewPoint(int u) { return (++PTop)->u = u, PTop; }

inline void Dfs(int u) {
    int v;
    edge *E;
    point *&U = Po[u], *V;
    while (!To[u].empty()) {
        E = To[u].top(), To[u].pop(), v = E->Next(u);
        if (E->Use) continue;
        E->Use = 1;
        if (U->Next) {
            V = U, U = NewPoint(u);
            U->Next = V->Next;
        }
        if (Po[v] && !Po[v]->S) {
            (U->Next = Po[v])->S = 1;
            continue;
        }
        
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 1; i <= m; ++i) std::cin >> x >> y, AddEdge(x, y);
    for (int i = 1; i <= n; ++i) {
        if (Deg[i] & 1) Last = Last ? (AddEdge(Last, i), 0) : i;
    }
    if ((ETop - Edge) & 1) AddEdge(1, 1);
    Po[1] = NewPoint(1), Dfs(1);
    return 0;
}