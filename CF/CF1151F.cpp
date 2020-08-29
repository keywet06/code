#include <bits/stdc++.h>
const int N = 105;
const int mod = 1000000007;
void add(int &x, int y) {
    x += y;
    if (x >= mod) x -= mod;
}
int n, m, k, z;
int a[N];
int re[N][N];
int power(int a, int b) {
    int s = 1;
    while (b) {
        if (b & 1) s = 1ll * s * a % mod;
        a = 1ll * a * a % mod;
        b >>= 1;
    }
    return s;
}
struct Matrix {
    int s[N][N];
    void clear() { memset(s, 0, sizeof(s)); }
    void init() {
        clear();
        for (int i = 0; i <= m; ++i) s[i][i] = 1;
    }
    int *operator[](int x) { return s[x]; }
} A, B;
Matrix operator*(Matrix a, Matrix b) {
    Matrix c;
    c.clear();
    for (int i = 0; i <= m; ++i)
        for (int j = 0; j <= m; ++j)
            for (int k = 0; k <= m; ++k)
                c[i][j] = (c[i][j] + 1ll * a[i][k] * b[k][j]) % mod;
    return c;
}
Matrix power(Matrix a, int b) {
    Matrix s;
    s.init();
    while (b) {
        if (b & 1) s = s * a;
        a = a * a;
        b >>= 1;
    }
    return s;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin >> n >> k;
    for (int i = 1; i <= n; ++i) std::cin >> a[i], z += a[i] ^ 1;
    for (int i = 0; i <= n; ++i) re[i][0] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= i; ++j)
            re[i][j] = (re[i - 1][j] + re[i - 1][j - 1]) % mod;
    int s = 0;
    for (int i = 1; i <= n; ++i)
        if (i <= z && a[i]) ++s;
    m = std::min(n - z, z);
    B[0][s] = 1;
    for (int i = 0; i <= m; ++i) {
        add(A[i][i], (re[z][2] + re[n - z][2]) % mod);
        add(A[i][i], 1ll * i * (n - z - i) % mod);
        add(A[i][i], 1ll * (z - i) * i % mod);
        if (i) add(A[i][i - 1], 1ll * i * i % mod);
        if (i < m) add(A[i][i + 1], 1ll * (z - i) * (n - z - i) % mod);
    }
    B = B * power(A, k);
    int ans = 1ll * B[0][0] * power(power(n * (n - 1) / 2, k), mod - 2) % mod;
    std::cout << ans << std::endl;
    return 0;
}