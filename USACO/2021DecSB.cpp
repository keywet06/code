#include <bits/stdc++.h>

template <typename Type1, typename Type2>
inline Type1 &Mid(Type1 &x, Type2 y) {
    return x < y ? x : (x = y);
}

using int64 = long long;

const int N = 600005;

int T, n, m, x, y, Min;
int Col[N], D1[N], D2[N];

int64 Ans;

std::vector<int> To[N], Po[N];

inline int64 sqr(int64 x) { return x * x; }

inline void Dfs(int u, int Co) {
    Col[u] = Co, Mid(Min, D2[u]);
    for (int v : To[u]) {
        if (!Col[v]) Dfs(v, Co);
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> T;
    while (T--) {
        std::cin >> n >> m;
        for (int i = 0; i <= n; ++i) To[i].clear(), Po[i].clear();
        memset(Col, 0, sizeof(int) * (n + 5));
        memset(D1, 63, sizeof(int) * (n + 5));
        memset(D2, 63, sizeof(int) * (n + 5));
        while (m--) {
            std::cin >> x >> y;
            To[x].push_back(y);
            To[y].push_back(x);
        }
        Dfs(1, 1);
        if (Col[n]) {
            std::cout << 0 << std::endl;
            continue;
        }
        Dfs(n, 2);
        Min = D1[0], Ans = 1e17;
        for (int i = 1; i <= n; ++i) {
            if (Col[i] == 1) D1[i] = 0;
            if (Col[i] == 2) D2[i] = 0;
            Mid(D1[i], D1[i - 1] + 1);
            Mid(D2[i], D2[i - 1] + 1);
        }
        for (int i = n; i; --i) {
            Mid(D1[i], D1[i + 1] + 1);
            Mid(D2[i], D2[i + 1] + 1);
        }
        for (int i = 1; i <= n; ++i) Po[D1[i]].push_back(i);
        for (int i = 0; i < n; ++i) {
            for (int u : Po[i]) Dfs(u, 1);
            Mid(Ans, sqr(i) + sqr(Min));
        }
        std::cout << Ans << std::endl;
    }
    return 0;
}