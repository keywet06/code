#include <bits/stdc++.h>

const int N = 105;

int n, m;
int a[N][N], f[N][N], Min[N], g[N][N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) std::cin >> a[i][j];
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) g[i][i] += Min[j] = a[i][j];
        for (int j = i + 1; j <= n; ++j) {
            for (int k = 1; k <= m; ++k) g[i][j] += Min[k] = std::min(Min[k], a[j][k]);
        }
    }
    for (int j = 1; j <= n; ++j) {
        f[j][j] = g[j][j];
        for (int i = j - 1; i; --i) {
            f[i][j] = INT_MAX;
            for (int k = i; k < j; ++k) f[i][j] = std::min(f[i][j], f[i][k] + f[k + 1][j] - g[i][j]);
        }
    }
    std::cout << f[1][n] * 2 << std::endl;
    return 0;
}