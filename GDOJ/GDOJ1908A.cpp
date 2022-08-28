#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

#define templ template <typename Type1, typename Type2>
templ inline Type1 Min(Type1 x, Type2 y) { return x < y ? x : y; }
templ inline Type1 Max(Type1 x, Type2 y) { return y < x ? x : y; }
templ inline Type1 &Mid(Type1 &x, Type2 y) { return x < y ? x : x = y; }
templ inline Type1 &Mad(Type1 &x, Type2 y) { return y < x ? x : x = y; }
#undef templ

#define templ template <typename Type1, typename Type2, typename... Args>
templ inline Type1 Min(Type1 x, Type2 y, Args... args) { return Min(Min(x, y), args...); }
templ inline Type1 Max(Type1 x, Type2 y, Args... args) { return Max(Max(x, y), args...); }
templ inline Type1 &Mid(Type1 &x, Type2 y, Args... args) { return Mid(Mid(x, y), args...); }
templ inline Type1 &Mad(Type1 &x, Type2 y, Args... args) { return Mad(Mad(x, y), args...); }
#undef templ

const int N = 1005;

int n;
int px[N], py[N];

std::vector<int> To[N];

int Clock, SCnt, StaTop;
int Vis[N], Dfn[N], Low[N], Sta[N], SId[N];
std::vector<int> SPo[N], Get[N];

int sx[N], sy[N];

int AnsSize, Size[N];
int Sm[N][N], f[N][N], Ans[N], t[N];

inline void Tarjan(int u) {
    Vis[u] = 1, Low[u] = Dfn[u] = ++Clock, Sta[++StaTop] = u;
    for (auto v : To[u]) {
        if (!Dfn[v]) {
            Tarjan(v), Mid(Low[u], Low[v]);
        } else if (Vis[v]) {
            Mid(Low[u], Low[v]);
        }
    }
    if (Dfn[u] == Low[u]) {
        ++SCnt;
        while (Sta[StaTop + 1] != u) {
            Vis[Sta[StaTop]] = 0, SId[Sta[StaTop]] = SCnt;
            SPo[SCnt].push_back(Sta[StaTop--]);
        }
    }
}

inline void Dfs(int u) {
    if (Vis[u]) return;
    Vis[u] = 1, std::sort(Get[u].begin(), Get[u].end());
    Get[u].resize(std::unique(Get[u].begin(), Get[u].end()) - Get[u].begin());
    for (auto v : Get[u]) Dfs(v);
    memset(t, 127, sizeof(t)), t[0] = 0;
    int Si = 0;
    for (auto v : Get[u]) {
        for (int i = 1; i <= Size[v]; ++i) Mid(t[i], f[v][i]);
        Mad(Si, Size[v]);
    }
    Mad(AnsSize, Size[u] = Si + SPo[u].size());
    memset(f[u], 127, (Size[u] + 1) * sizeof(int));
    for (int i = 0; i <= SPo[u].size(); ++i) {
        for (int j = 0; j <= Si; ++j) Mid(f[u][i + j], Sm[u][i] + t[j]);
    }
    for (int i = 0; i <= Size[u]; ++i) Mid(Ans[i], f[u][i]);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n;
    for (int i = 1, f, x; i <= n; ++i) {
        std::cin >> px[i] >> py[i] >> f, To[i].reserve(f);
        while (f--) std::cin >> x, To[i].push_back(x);
    }
    for (int i = 1; i <= n; ++i) {
        if (!Dfn[i]) Tarjan(i);
    }
    for (int i = 1; i <= SCnt; ++i) {
        for (auto u : SPo[i]) {
            for (auto v : To[u]) Get[SId[v]].push_back(i);
        }
        std::sort(SPo[i].begin(), SPo[i].end(), [](int x, int y) { return px[x] < px[y]; });
        int s = 0, m = SPo[i].size();
        for (int j = 1; j <= m; ++j) {
            int x = px[SPo[i][j - 1]], y = py[SPo[i][j - 1]];
            Sm[i][j] = INT_MAX, s += x;
            for (int k = 0; k < m; ++k) {
                int nx = px[SPo[i][k]], ny = py[SPo[i][k]];
                if (k < j) {
                    Mid(Sm[i][j], s - nx + ny);
                } else {
                    Mid(Sm[i][j], s - x + ny);
                }
            }
        }
    }
    memset(Ans, 127, sizeof(Ans));
    for (int i = 1; i <= n; ++i) {
        if (!Vis[i]) Dfs(i);
    }
    for (int i = 1; i <= AnsSize; ++i) std::cout << Ans[i] << '\n';
    return 0;
}