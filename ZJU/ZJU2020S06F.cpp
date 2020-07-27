#include <bits/stdc++.h>
const int N = 100005;
const int M = 505;
const int K = 15;
int n, k, x, ans, max;
int g[N], a[N], v[N];
int f[M][K];
int main() {
    std::cin >> n >> k;
    for (int i = 1; i <= n * k; ++i) {
        std::cin >> x;
        ++g[x];
    }
    for (int i = 1; i <= n; ++i) {
        std::cin >> x;
        ++a[x];
    }
    for (int i = 1; i <= k; ++i) std::cin >> v[i];
    for (int i = 1; i < N; ++i) {
        if (g[i] && a[i]) {
            for (int j = 1; j <= k; ++j) {
                for (int k = j; k <= g[i]; ++k) {
                    for (int l = 1; l <= a[i]; ++l) {
                        f[k][l] = std::max(f[k][l], f[k - j][l - 1] + v[j]);
                        max = std::max(max, f[k][l]);
                    }
                }
            }
            ans += max;
            for (int j = 1; j <= k; ++j) {
                for (int k = j; k <= g[i]; ++k) {
                    for (int l = 1; l <= a[i]; ++l) {
                        f[k][l] = 0;
                    }
                }
            }
            max = 0;
        }
    }
    std::cout << ans << std::endl;
    return 0;
}