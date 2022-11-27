#include <bits/stdc++.h>

using int64 = long long;

struct Edge {
    int64 u, v, w;
};

const int N = 200005;

int n, m, Cnt;
int f[N];

int64 Sum;
int64 Size[N];

Edge Ed[N];

std::vector<int> To[N];

inline int Find(int u) { return f[u] == u ? u : f[u] = Find(f[u]); }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) f[i] = i, Size[i] = 1;
    for (int i = 1; i <= m; ++i) {
        std::cin >> Ed[i].u >> Ed[i].v >> Ed[i].w;
        To[Ed[i].u].push_back(Ed[i].v), To[Ed[i].v].push_back(Ed[i].u);
    }
    std::sort(Ed + 1, Ed + m + 1, [](Edge a, Edge b) { return a.w < b.w; });
    for (int i = 1; i <= m; ++i) {
        int u = Find(Ed[i].u), v = Find(Ed[i].v);
        if (u == v) continue;
        if (Ed[i].w - i > Sum - Cnt) return std::cout << "No" << '\n', 0;
        Sum += Size[u] * Size[v];
        if (To[u].size() > To[v].size()) std::swap(u, v);
        for (auto t : To[u]) {
            if (Find(t) == v) ++Cnt;
            To[v].push_back(t);
        }
        To[u].clear(), f[u] = v, Size[v] += Size[u];
    }
    std::cout << "Yes" << '\n';
    return 0;
}