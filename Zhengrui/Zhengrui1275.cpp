#include <bits/stdc++.h>

#define fo(i, a, b) for (int i = a; i <= b; i++)
#define fd(i, a, b) for (int i = a; i >= b; i--)
const double eps = 1e-15;
const int C = 256;
const int N = 2000;
const int Np = N + 5;
const int Ni = 15;
const int _1_leftNi = 1 << Ni;
double num;
double f[C][_1_leftNi], g[C][_1_leftNi];
int a[Np];
int n, k, m;
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> k >> m;
    num = 1.0 / k;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }
    std::sort(a + 1, a + n + 1);
    g[1][(1 << n) - 1] = 1;
    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j < 1 << n; ++j) {
            if (g[i][j] > eps || f[i][j] > eps) {
                int c = 0;
                double x = f[i][j] * num, y = g[i][j] * num;
                for (int l = 1; l <= k; ++l) {
                    while (c < n && (!(j >> c & 1) || a[c + 1] < l)) {
                        c++;
                    }
                    if (c >= n) {
                        f[i + 1][j] += x;
                        g[i + 1][j] += y;
                    } else {
                        f[i + 1][j ^ (1 << c)] += x + y * l;
                        g[i + 1][j ^ (1 << c)] += y;
                    }
                }
            }
        }
    }
    double ans = 0;
    for (int i = 0; i < 1 << n; ++i) {
        ans += f[m + 1][i];
    }
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(10)
              << ans << std::endl;
    return 0;
}
