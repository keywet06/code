#include <bits/stdc++.h>

using Veci1 = std::vector<int>;
using Vecd1 = std::vector<double>;
using Vecd2 = std::vector<Vecd1>;
using Vecd3 = std::vector<Vecd2>;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    int n, l, k;
    std::cin >> n >> l >> k;
    Vecd1 p(n);
    for (double &x : p) std::cin >> x, x /= 100;
    Veci1 a(n);
    for (int &x : a) std::cin >> x;
    Vecd3 f(n + 1, Vecd2(n + 1, Vecd1(2 * n + 1)));
    f[0][0][n + k] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            for (int k = 0; k <= 2 * n; ++k) {
                double u = f[i][j][k];
                if (a[i] == -1) {
                    if (k) f[i + 1][j + 1][k - 1] += u * p[i];
                    f[i + 1][j][k] += u * (1 - p[i]);
                } else {
                    f[i + 1][j + 1][std::min(k + a[i], 2 * n)] += u * p[i];
                    f[i + 1][j][k] += u * (1 - p[i]);
                }
            }
        }
    }
    double Ans = 0;
    for (int i = l; i <= n; ++i) {
        for (int j = n; j <= 2 * n; ++j) Ans += f[n][i][j];
    }
    std::cout << std::fixed << std::setprecision(6);
    std::cout << Ans << std::endl;
    return 0;
}