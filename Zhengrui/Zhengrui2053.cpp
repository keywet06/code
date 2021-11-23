#include <bits/stdc++.h>

const int N = 4005;
const int M = N * N >> 2;

int n, c, x, y;
int pl[M], pr[M];
int a[N][N], f[N][N];

inline void dfs(int l, int r) {
    if (l < 0 || r > n || f[l][r]) return;
    f[l][r] = 1;
    if (l == 1 && r == n) std::cout << c << std::endl, exit(0);
    if (a[l - 1][r + 1] <= c) dfs(l - 1, r + 1);
    for (int i = r + 2; i <= n; i += 2) {
        if (f[r + 1][i]) dfs(l, i);
    }
    for (int i = l - 2; i > 0; i -= 2) {
        if (f[i][l - 1]) dfs(i, r);
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i < n; ++i) {
        for (int j = i + 1; j <= n; j += 2) {
            std::cin >> a[i][j], pl[a[i][j]] = i, pr[a[i][j]] = j;
        }
    }
    for (c = 1; c < M; ++c) {
        x = pl[c], y = pr[c];
        if (x + 1 == y || f[x + 1][y - 1]) dfs(x, y);
    }
    return 0;
}