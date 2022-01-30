#include <bits/stdc++.h>
 
const int N = 55;
 
char Ch[N];
 
int n;
int Num[N];
int Col[N][N];
 
inline bool check(int x, int y, int z) { return x + y + z == 6 && x != y; }
 
inline void dfs(int u, int v) {
    if (u == v) return dfs(1, v + 1);
    if (v > n) {
        std::cout << "Yes" << '\n';
        for (int i = 1; i < n; ++i) {
            for (int j = i + 1; j <= n; ++j) std::cout << Ch[Col[i][j]];
            std::cout << '\n';
        }
        exit(0);
    }
    for (int c = 1; c <= 3; ++c) {
        if (!Num[c]) continue;
        int flag = 0;
        for (int x = 1; x < u; ++x) {
            if (check(Col[x][u], Col[x][v], c) && (flag = 1)) break;
        }
        if (flag) continue;
        --Num[c], Col[u][v] = c;
        dfs(u + 1, v), ++Num[c];
    }
}
 
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n, Ch[1] = 'R', Ch[2] = 'B', Ch[3] = 'W';
    if (n % 3 == 2) return std::cout << "No" << '\n', 0;
    Num[1] = Num[2] = Num[3] = n * (n - 1) / 6;
    dfs(1, 2);
    std::cout << "No" << '\n';
    return 0;
}