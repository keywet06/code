#include <bits/stdc++.h>

#define templ template <typename Type1, typename Type2>
templ inline Type1 &Mid(Type1 &x, Type2 y) { return x < y ? x : x = y; }
templ inline Type1 &Mad(Type1 &x, Type2 y) { return x > y ? x : x = y; }
#undef templ

#define templ template <typename Type1, typename Type2, typename... Args>
templ inline Type1 &Mid(Type1 &x, Type2 y, Args... args) { return Mid(Mid(x, y), args...); }
templ inline Type1 &Mad(Type1 &x, Type2 y, Args... args) { return Mad(Mad(x, y), args...); }
#undef templ

using int64 = long long;

template <typename Type>
using Pq = std::priority_queue<Type, std::vector<Type>, std::greater<Type> >;

const int K = 20;
const int N = 100005;
const int M = 200005;

int n, m;
int Eu[M], Ev[M], Ew[M], Vis[M], Type[K];

int64 Dis[K][N];

std::vector<std::pair<int, int> > To[N];

inline void Dij(int S, int64 *Dis) {
    memset(Vis, 0, sizeof(int) * N);
    memset(Dis, 1, sizeof(int64) * N);
    Pq<std::pair<int, int> > Que;
    Que.emplace(Dis[S] = 0, S), Vis[S] = 1;
    while (Que.size()) {
        auto [D, u] = Que.top();
        if (Dis[u] != D) continue;
        Que.pop(), Vis[u] = 0;
        for (auto [v, d] : To[u]) {
            if (D + d < Dis[v]) {
                Dis[v] = D + d;
                if (!Vis[v]) Vis[v] = 1, Que.emplace(D + d, v);
            }
        }
    }
}

int64 Ans = INT64_MAX;

inline void Solve(int64 Tl, int64 Tr, int l) {
    // Tl - x = Tr + x
    // 2x = Tl - Tr
    Mid(Ans, Tl, Tr + l);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> m;
    for (int i = 1, u, v, w; i <= m; ++i) {
        std::cin >> u >> v >> w;
        To[u].emplace_back(v, w);
        To[v].emplace_back(u, w);
        Eu[i] = u, Ev[i] = v, Ew[i] = w;;
    }
    int k;
    std::cin >> k;
    for (int i = 0, u; i < k; ++i) std::cin >> u, Dij(u, Dis[i]);
    for (int i = 1, u, v, w; i <= m; ++i) {
        u = Eu[i], v = Ev[i], w = Ew[i];
        std::vector<std::pair<int, int> > Vec;
        for (int j = 0; j < k; ++j) {
            Type[j] = Dis[j][u] + w == Dis[j][v];
            // Dis[j][u] + x = Dis[j][u] + (w - x)
            // 2x = w + Dis[j][u] - Dis[j][u]
            if (std::abs(Dis[j][u] - Dis[j][v]) != w) Vec.emplace_back(w + Dis[j][u] - Dis[j][u], k);
        }
        std::sort(Vec.begin(), Vec.end());
        int Nex = Vec.size() ? Vec.front().first : w * 2;
        
        for (int i = 0; i < n; ++i) {

        }
    }
    return 0;
}