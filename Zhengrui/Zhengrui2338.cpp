#include <bits/stdc++.h>

const int N = 500005;

int n, m;
int eu[N], ev[N], ec[N], Ans[N], Deep[N], Fa[N], EId[N], f[N];

std::vector<int> Ed[N];

inline void Dfs(int u, int F) {
    f[u] = u, Fa[u] = F, Deep[u] = Deep[F] + 1;
    for (auto e : Ed[u]) {
        int v = eu[e] + ev[e] - u;
        if (v == F) continue;
        EId[v] = e, Dfs(v, u);
    }
}

inline int Find(int u) { return f[u] = u == f[u] ? Ans[EId[u]] ? Find(Fa[u]) : u : Find(f[u]); }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        std::cin >> eu[i] >> ev[i] >> ec[i];
        if (ec[i] == 1) {
            Ed[eu[i]].push_back(i);
            Ed[ev[i]].push_back(i);
        }
    }
    Dfs(1, 1);
    int Cnt = 0;
    for (int i = 1; i <= m; ++i) {
        if (Ans[i] || ec[i] == 1 && (Ans[i] = ++Cnt)) continue;
        int u = eu[i], v = ev[i];
        std::vector<int> Ids;
        while (u != v) {
            if (Deep[u = Find(u)] < Deep[v = Find(v)]) std::swap(u, v);
            if (u != v) Ids.push_back(EId[u]), f[u] = f[Fa[u]];
        }
        std::sort(Ids.begin(), Ids.end());
        for (auto u : Ids) Ans[u] = ++Cnt;
        Ans[i] = ++Cnt;
    }
    for (int i = 1; i <= m; ++i) std::cout << Ans[i] << " \n"[i == m];
    return 0;
}