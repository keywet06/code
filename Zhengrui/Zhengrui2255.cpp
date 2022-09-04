#include <bits/stdc++.h>

const int N = 1005;
const int M = 2005;
const int Q = 100005;

bool r[N][N];

int n, m, q;
int f[N];
int eu[M], ev[M], ew[M], p[M];
int Ans[Q], qu[Q], qv[Q];

inline int find(int u) { return f[u] == u ? u : f[u] = find(f[u]); }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> m >> q;
    for (int i = 1; i <= m; ++i) std::cin >> eu[i] >> ev[i] >> ew[i], p[i] = i;
    std::sort(p + 1, p + m + 1, [](int x, int y) { return ew[x] < ew[y]; });
    for (int i = 1; i <= q; ++i) std::cin >> qu[i] >> qv[i], Ans[i] = -1;
    for (int i = 1; i <= n; ++i) f[i] = i;
    for (int i = 1; i <= m; ++i) {
        for (int j = i; j <= m; ++j) r[f[eu[p[j]]]][f[ev[p[j]]]] = r[f[ev[p[j]]]][f[eu[p[j]]]] = true;
        for (int j = 1; j <= q; ++j) Ans[j] = Ans[j] == -1 && r[f[qu[j]]][f[qv[j]]] ? ew[p[i - 1]] : Ans[j];
        f[f[eu[p[i]]]] = f[ev[p[i]]];
        for (int j = 1; j <= n; ++j) find(j);
    }
    for (int i = 1; i <= q; ++i) std::cout << Ans[i] << '\n';
    return 0;
}