#include <bits/stdc++.h>

using int64 = long long;

const int C = 16;
const int P = 998244353;

int n;
int Num[C], p[C];

int64 Ans;

inline void Dfs(int u) {
    if (u == n + 1) return void(++Ans);
    for (int x = 1; x < n; ++x) {
        if (!Num[x] || x == p[u]) continue;
        --Num[x];
        for (int y = x + 1; y <= n; ++y) {
            if (!Num[y] || y == p[u]) continue;
            --Num[y], Dfs(u + 1), ++Num[y];
        }
        ++Num[x];
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> p[i], Num[i] = 2;
    Dfs(1);
    std::cout << Ans % P << std::endl;
    return 0;
}