#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

#define Deb std::cerr
#define Delin Deb << "[Debug] at Line " << __LINE__
#define Debug Delin << " : "
#define Deline Delin << std::endl

const int N = 11005;
const int M = 20000000;

int S, T, n, Cnt = 1;
int Head[N], Dis[N], Vis[N], Cur[N];
int Next[M], To[M], Flow[M];

inline void Insert(int x, int y, int z) {
    Next[++Cnt] = Head[x], Head[x] = Cnt;
    To[Cnt] = y, Flow[Cnt] = z;
}

inline void Addedge(int x, int y, int z) { Insert(x, y, z), Insert(y, x, 0); }

inline int SPFA() {
    std::queue<int> Que;
    memset(Dis, 127, sizeof(Dis));
    Que.push(T), Dis[T] = 0, Vis[T] = 1;
    while (!Que.empty()) {
        int u = Que.front();
        Que.pop(), Vis[u] = 0;
        for (int e = Head[u]; e; e = Next[e]) {
            if (Flow[e ^ 1] && Dis[u] + 1 < Dis[To[e]]) {
                Dis[To[e]] = Dis[u] + 1;
                if (!Vis[To[e]]) Que.push(To[e]), Vis[To[e]] = 1;
            }
        }
    }
    return Dis[S] != Dis[0];
}

inline int Dfs(int u, int limit) {
    if (u == T) return limit;
    int rlow = 0, used = 0;
    for (int &e = Cur[u]; e; e = Next[e]) {
        if (!Flow[e] || Dis[To[e]] != Dis[u] - 1) continue;
        if (!(rlow = Dfs(To[e], std::min(limit - used, Flow[e])))) continue;
        used += rlow, Flow[e] -= rlow, Flow[e ^ 1] += rlow;
        if (used == limit) return used;
    }
    return used;
}

inline int Dinic() {
    int Ans = 0;
    while (SPFA()) {
        memcpy(Cur, Head, sizeof(Head));
        Ans += Dfs(S, 1e9);
    }
    return Ans;
}

std::string s;

int aMin[N], aMax[N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    
    return 0;
}