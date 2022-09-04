#include <bits/stdc++.h>

const int N = 1200005;

int T, n;

std::vector<int> To[N];

inline void AddEdge(int u, int v) {
    To[u].push_back(v);
    To[v].push_back(u);
}

int Sum;
int Vis[N];

inline void TestDfs(int u, int Fa) {
    Vis[u] = 1;
    for (auto v : To[u]) {
        if (v == Fa) continue;
        if (Vis[v]) throw "There is at least one cycle";
        TesttDfs(v, u);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> T;
    while (T--) {
        std::cin >> n;
        for (int i = 1; i <= n << 1; ++i) To[i].clear();
        for (int i = 1; i <= n; ++i) {
            int k, u;
            std::cin >> k;
            while (k--) std::cin >> u, AddEdge(u, n + i);
        }
        try {
            Sum = 0;
            TestDfs()
        } catch (std::string Err) {
            // std::cerr << Err << std::endl;
            std::cout << 0 << '\n';
            continue;
        }
    }
    return 0;
}