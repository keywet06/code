#include <bits/stdc++.h>

const int N = 100005;
const int M = 200005;
const int Q = 100005;

struct Edge {
    int u, v, w;
    Edge() {}
    Edge(int cu, int cv, int cw) : u(cu), v(cv), w(cw) {}
};

int n, m, q;
int f[N];
int Ans[Q], qu[Q], qv[Q];

Edge e[M];

inline int find(int u) { return f[u] == u ? u : f[u] = find(f[u]); }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> m >> q;
    for (int i = 1; i <= m; ++i) std::cin >> e[i].u >> e[i].v >> e[i].w;
    std::sort(e + 1, e + m + 1, [](Edge x, Edge y) { return x.w < y.w; });
    for (int i = 1; i <= q; ++i) std::cin >> qu[i] >> qv[i], Ans[i] = -1;
    for (int i = 1; i <= n; ++i) f[i] = i;
    for (int i = 1; i <= m; ++i) {
        
    }
    for (int i = 1; i <= q; ++i) std::cout << Ans[i] << '\n';
    return 0;
}