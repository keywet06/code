#include <bits/stdc++.h>
const int N = 1000;
const int Np = N + 5;
int n, t, k;
int a[Np], p[Np], b[Np];
long long f[Np];
long long c[Np][Np];
int main() {
    std::cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        p[i] = p[i - 1] + a[i];
    }
    for (int i = 1; i <= n; ++i) {
        t = 0;
        for (int j = i; j <= n; ++j) {
            b[a[j]] = 1;
            while (b[t]) ++t;
            c[i - 1][j] = t * (p[j] - p[i - 1]);
        }
        memset(b, 0, sizeof(b));
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = std::max(i - k, 0); j <= n; ++j) {
            f[i] = std::max(f[i], f[j] + c[j][i]);
        }
    }
    std::cout << f[n] << std::endl;
    return 0;
}