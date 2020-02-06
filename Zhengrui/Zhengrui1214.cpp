#include <bits/stdc++.h>
const int N = 1500;
const int Np = N + 5;
int n, m, ans, x, y;
int d[Np][Np], w[Np][Np], h[Np][Np];
std::string stb;
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        std::cin >> stb;
        for (int j = 1; j <= n; ++j) {
            d[i][j] = stb[j - 1] == '1';
        }
    }
    for (int i = n; i; --i) {
        for (int j = n; j; --j) {
            w[i][j] = d[i][j] * (w[i][j + 1] + 1);
            h[i][j] = d[i][j] * (h[i + 1][j] + 1);
        }
    }
    for (int i = 1; i <= m; ++i) {
        std::cin >> x >> y;
        ans = 0;
        for (int j = 1; j <= n - x + 1; ++j) {
            for (int k = 1; k <= n - y + 1; ++k) {
                ans += h[j][k] >= x && w[j][k] >= y && h[j][k + y - 1] >= x &&
                  w[j + x - 1][k] >= y;
            }
        }
        std::cout << ans << std::endl;
    }
    return 0;
}