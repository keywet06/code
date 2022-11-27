#include <bits/stdc++.h>

using int64 = long long;

const int C = 6;
const int d[C][2] = {{-1, -1}, {-1, 0}, {0, -1}, {1, 1}, {1, 0}, {0, 1}};
const int64 D[C] = {
    d[0][0] + d[0][1] * (1ll << 32), d[1][0] + d[1][1] * (1ll << 32), d[2][0] + d[2][1] * (1ll << 32),
    d[3][0] + d[3][1] * (1ll << 32), d[4][0] + d[4][1] * (1ll << 32), d[5][0] + d[5][1] * (1ll << 32),
};
const int64 Base = 1e9 + 5;

inline int64 GetPos(int x, int y) { return x + Base | y + Base << 32; }

const int N = 700005;

int n, m;
int Id[N], Kind[N], To[N][C], Size[N], Let[N];

int64 Pos[N];

std::unordered_map<int64, int> Map;

inline int GetId(int64 u) {
    int &x = Map[u];
    return x ? x : (Pos[n + 1] = u, x = ++n);
}

inline void Dfs(int u, int k) {
    Kind[u] = k, ++Size[k];
    for (int i = 0, v; i < C; ++i) {
        if (Kind[To[u][i]] == -1 && (v = To[To[u][i]][i]) && Kind[v] == 0) Dfs(v, k);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> m;
    for (int i = 1, x, y; i <= m; ++i) {
        std::cin >> x >> y;
        int64 u = GetPos(x, y);
        Id[i] = GetId(u), Kind[Id[i]] = -1;
        for (int j = 0; j < C; ++j) {
            int v = GetId(u + D[j]);
            To[Id[i]][j] = v, To[v][(j + (C >> 1)) % C] = Id[i];
        }
    }
    int k = 0;
    for (int i = 1; i <= m; ++i) {
        int u = Id[i], Ans = 0;
        for (int j = 0, v; j < C; ++j) {
            if (Kind[To[u][j]] != -1) {
                ++Ans;
            } else if (Kind[v = To[To[u][j]][j]] != -1) {
                if (Kind[v] == 0) Dfs(v, ++k);
                if (Let[Kind[v]] != i) Let[Kind[v]] = i, Ans += Size[Kind[v]];
            }
        }
        std::cout << Ans << '\n';
    }
    return 0;
}