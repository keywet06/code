#include <bits/stdc++.h>

#define Deb std::cerr
#define Delin Deb << "[Debug] at Line " << __LINE__
#define Debug Delin << " : "
#define Deline Delin << std::endl

using int64 = long long;

const int dx[4] = {-1, 0, 1, 1};
const int dy[4] = {1, 1, 1, 0};

const int C = 20;
const int N = 705;
const int M = N * N;

int n, m, DfnClock, SplitEdgeNum;
int Dfn[M], Low[M], Dep[M], Spl[M], Fa[M][C], Ed[M][4];

std::vector<std::pair<int, int> > To[M];

inline int GetId(int x, int y) { return x * m + y; }

inline void Dfs(int u, int F) {
    Fa[u][0] = F, Dep[u] = Dep[F] + 1, Dfn[u] = Low[u] = ++DfnClock;
    for (int i = 1; i < C; ++i) Fa[u][i] = Fa[Fa[u][i - 1]][i - 1];
    for (auto p : To[u]) {
        int v = p.first, e = p.second;
        if (v == F) continue;
        if (!Dfn[v]) {
            Dfs(v, u);
            if (Low[v] == Dfn[v]) Ed[e >> 2][e & 3] = 2, ++SplitEdgeNum, Spl[v] = 1;
        }
        Low[u] = std::min(Low[u], Low[v]);
    }
}

inline void DfsSplit(int u) {
    for (auto p : To[u]) {
        int v = p.first;
        if (Fa[v][0] == u) Spl[v] += Spl[u], DfsSplit(v);
    }
}

inline int Up(int u, int x) {
    while (x) u = Fa[u][__builtin_ctz(x)], x &= x - 1;
    return u;
}

inline int Lca(int u, int v) {
    if (Dep[u] < Dep[v]) std::swap(u, v);
    u = Up(u, Dep[u] - Dep[v]);
    if (u == v) return u;
    for (int x = 31 - __builtin_clz(Dep[u]); x >= 0; --x) {
        if (Fa[u][x] != Fa[v][x]) u = Fa[u][x], v = Fa[v][x];
    }
    return Fa[u][0];
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> m;
    int VNum = 0, ANum = (n - 1) * m + n * (m - 1) + 2 * (n - 1) * (m - 1), TNum = 0;
    for (int i = 1; i <= n; ++i) {
        std::string s;
        std::cin >> s;
        for (int j = 1; j <= m; ++j) {
            int u = GetId(i, j), x = s[j - 1] - (s[j - 1] <= '9' ? '0' : 'A' - 10);
            for (int c = 0; c < 4; ++c) {
                if (x & (1 << c)) {
                    TNum += !(c & 1);
                    int v = GetId(i + dx[c], j + dy[c]);
                    Ed[u][c] = 1;
                    To[u].emplace_back(v, u << 2 | c);
                    To[v].emplace_back(u, u << 2 | c);
                    ++VNum;
                }
            }
        }
    }
    Dfs(GetId(1, 1), 0), DfsSplit(GetId(1, 1));
    int64 Ans = int64(VNum - SplitEdgeNum) * (ANum - VNum - TNum);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int u = GetId(i, j);
            for (int c = 0; c < 4; ++c) {
                if (Ed[u][c]) continue;
                int x = i + dx[c], y = j + dy[c];
                if (x > 0 && y > 0 && x <= n && y <= m) {
                    int Flag = 0;
                    if (c == 0) {
                        Flag = Ed[GetId(i - 1, j)][2];
                    } else if (c == 2) {
                        Flag = Ed[GetId(i + 1, j)][0];
                    }
                    if (Flag == 0) {
                        int v = GetId(x, y), o = Lca(u, v);
                        Ans += Spl[u] + Spl[v] - 2 * Spl[o];
                    } else if (Flag == 1) {
                        ++Ans;
                    } else {
                        int v = GetId(x, y), o = Lca(u, v);
                        int p = GetId(i, y), q = GetId(x, j);
                        if (p != Fa[q][0]) std::swap(p, q);
                        assert(p == Fa[q][0]);
                        Ans += Dep[q] > Dep[o] && (Dep[q] <= Dep[u] && Up(u, Dep[u] - Dep[q]) == q ||
                                                   Dep[q] <= Dep[v] && Up(v, Dep[v] - Dep[q]) == q);
                    }
                }
            }
        }
    }
    std::cout << Ans << '\n';
    return 0;
}