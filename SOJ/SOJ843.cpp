#include <bits/stdc++.h>
const int N = 5005;
int ans = N * N, n, m, sx, sy, tx, ty;
char str[N];
std::bitset<N> b[N];
inline void dfs(int x, int y, int z) {
    if (z >= ans) {
        return;
    }
    if (x == tx && y == ty) {
        ans = z;
        return;
    }
    b[x][y] = 0;
    int t;
    if (b[x][y + 1]) {
        t = y + 1;
        while (b[x][t + 1]) ++t;
        dfs(x, t, z + 1);
    }
    if (b[x][y - 1]) {
        t = y - 1;
        while (b[x][t - 1]) --t;
        dfs(x, t, z + 1);
    }
    if (b[x + 1][y]) {
        t = x + 1;
        while (b[t + 1][y]) ++t;
        dfs(t, y, z + 1);
    }
    if (b[x - 1][y]) {
        t = x - 1;
        while (b[t - 1][y]) --t;
        dfs(t, y, z + 1);
    }
    b[x][y] = 1;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m >> sx >> sy >> tx >> ty;
    for (int i = 1; i <= n; ++i) {
        std::cin >> str + 1;
        for (int j = 1; j <= m; ++j) {
            b[i][j] = str[j] == '.';
        }
    }
    dfs(sx, sy, 0);
    std::cout << (ans == N * N ? -1 : ans) << std::endl;
    return 0;
}