#include <bits/stdc++.h>
const int N = 105;
const int mod = 998244353;
int n, k;
int a[N];
long long f[N][N][N], g[N][N][N];
int main() {
    std::cin >> n >> k;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    for (int L = n; L; --L) {
        for (int R = 1; R <= n; ++R) {
            for (int K = 1; K <= k; ++K) {
                for (int i = L; i <= R; ++i) {
                    if (a[i] != a[R + 1])
                        f[L][R][K] =
                            (f[L][R][K] + (i > L ? g[L][i - 1][K - 1] : 1) *
                                              (i < R ? g[i + 1][R][K] : 1)) %
                            mod;
                }
                g[L][R][K] = (f[L][R][K] + g[L][R][K - 1]) % mod;
            }
        }
    }
    std::cout << f[1][n][k] << std::endl;
    return 0;
}