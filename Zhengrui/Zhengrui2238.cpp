#include <bits/stdc++.h>

using int64 = long long;

template <typename Type>
using SmallPriorityQueue = std::priority_queue<Type, std::vector<Type>, std::greater<Type> >;

const int N = 100005;

int n, m;

std::vector<std::pair<int, int> > To[N];

int From[N];
int64 Dis[N];

int Ban[N];

inline void ShortestPath(int S, int T) {
    memset(Dis, 15, sizeof(int64) * (n + 1));
    SmallPriorityQueue<std::pair<int64, int> > Que;
    Que.emplace(Dis[S] = 0, S);
    while (!Que.empty()) {
        auto Top = Que.top();
        Que.pop();
        int64 d = Top.first;
        int u = Top.second;
        if (Dis[u] != d) continue;
        if (u == T) break;
        for (int e = 0; e < To[u].size(); ++e) {
            int v = To[u][e].first, Len = To[u][e].second;
            if (Ban[u] != v && Dis[u] + Len < Dis[v]) {
                Dis[v] = Dis[u] + Len, From[v] = u;
                Que.emplace(Dis[v], v);
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> m;
    for (int i = 1, u, v, w; i <= m; ++i) {
        std::cin >> u >> v >> w;
        To[u].emplace_back(v, w);
    }
    if (n <= 1000) {
        for (int i = 2; i <= n; ++i) {
            ShortestPath(1, i);
            for (int u = i; u != 1; u = From[u]) Ban[From[u]] = u;
            int64 Ans = Dis[i];
            ShortestPath(1, i);
            for (int u = 1; u <= n; ++u) Ban[u] = 0;
            std::cout << ((Ans += Dis[i]) >= Dis[0] ? -1 : Ans) << '\n';
        }
        return 0;
    }
    return 0;
}