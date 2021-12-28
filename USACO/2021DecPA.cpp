#include <bits/stdc++.h>

template <typename Type>
using PriorityQueue =
    std::priority_queue<Type, std::vector<Type>, std::greater<Type>>;

using int64 = long long;

const int N = 100005;
const int M = 131072;
const int P = M + N;
const int L = P + N;
const int64 INF = 1e16;

using Pair = std::pair<int, int>;
using pair = std::pair<int64, int>;

int n, k, tc, tp, tl, tr;

int64 Dis1[L], Dis2[L], Dis[L];

std::vector<Pair> Get[L];

inline void Insert(int u, int v, int Val = 0) {
    Get[v].emplace_back(u, Val);
}

inline int Build(int u, int l, int r) {
    if (l == r) return M + l;
    int mid = l + r >> 1;
    Insert(u, Build(u << 1, l, mid));
    Insert(u, Build(u << 1 | 1, mid + 1, r));
    return u;
}

inline void Add(int u, int l, int r, int x, int y, int S) {
    if (l >= x && r <= y) return Insert(S, l == r ? M + l : u);
    int mid = l + r >> 1;
    if (x <= mid) Add(u << 1, l, mid, x, y, S);
    if (y > mid) Add(u << 1 | 1, mid + 1, r, x, y, S);
}

inline void Dij(int64 *Dis) {
    PriorityQueue<pair> Que;
    for (int i = 0; i < L; ++i) {
        if (Dis[i] != INF) Que.emplace(Dis[i], i);
    }
    while (!Que.empty()) {
        auto [dis, u] = Que.top();
        Que.pop();
        if (Dis[u] != dis) continue;
        for (auto [v, val] : Get[u]) {
            if (dis + val < Dis[v]) {
                Dis[v] = dis + val;
                Que.emplace(Dis[v], v);
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> k;
    Build(1, 1, n);
    for (int i = 1; i <= k; ++i) {
        std::cin >> tc >> tp >> tl >> tr;
        Insert(M + tc, P + i, tp);
        Add(1, 1, n, tl, tr, P + i);
    }
    for (int i = 0; i < L; ++i) Dis1[i] = Dis2[i] = Dis[i] = INF;
    Dis1[M + 1] = 0, Dis2[M + n] = 0;
    Dij(Dis1), Dij(Dis2);
    for (int i = 0; i < L; ++i) Dis[i] = std::min(INF, Dis1[i] + Dis2[i]);
    Dij(Dis);
    for (int i = M + 1; i <= M + n; ++i) {
        std::cout << (Dis[i] == INF ? -1 : Dis[i]) << '\n';
    }
    return 0;
}