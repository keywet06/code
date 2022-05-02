#include <bits/stdc++.h>

template <typename Type1, typename Type2>
inline Type1 &Mid(Type1 &x, Type2 y) {
    return x < y ? x : (x = y);
}

using int64 = long long;

const int N = 200005;
const int C = 85;

bool Used[N];

int n, MinId;

int64 Min, Ans;
int64 Dis[N];

std::vector<std::pair<int, int> > To[N];

inline void Dfs(int u, int Fa, int64 D) {
    Mid(Dis[u], std::abs(D));
    if (!Used[u] && Dis[u] < Min) Min = Dis[u], MinId = u;
    for (auto p : To[u]) {
        int v = p.first, w = p.second;
        if (v == Fa) continue;
        Dfs(v, u, D + w);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n;
    bool AllWIs1 = true;
    for (int i = 1, u, v, w; i < n; ++i) {
        std::cin >> u >> v >> w;
        To[u].emplace_back(v, w);
        To[v].emplace_back(u, w);
        AllWIs1 &= w == 1;
    }
    if (AllWIs1) return std::cout << n - 1 << std::endl, 0;
    memset(Dis, 127, sizeof(Dis)), MinId = 1;
    for (int i = 1; i <= n; ++i) Ans += Min, Min = Dis[0], Used[MinId] = true, Dis[MinId] = 0, Dfs(MinId, MinId, 0);
    std::cout << Ans << std::endl;
    return 0;
}