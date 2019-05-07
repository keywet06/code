int f[maxn][20];
for (int j = 0; j < 20; ++j) {
    for (int i = 1; i <= n; ++i) {
        f[i][j] = std::min(f[i][j - 1], f[i + (1 << (j + 1))][j - 1])
    }
}