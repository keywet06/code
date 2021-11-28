#include <bits/stdc++.h>

const int N = 55;

int n, m, s, x;
int a[N];

long double ans[N];
long double b[N][N];
long double c[N][N][N];
long double d[N][N][N][N];

int main() {
    freopen("hail.in", "r", stdin);
    freopen("hail.out", "w", stdout);
    std::cin >> n >> m;
    std::cout << std::fixed << std::setprecision(6);
    for (int i = 1; i <= n; ++i) std::cin >> a[i], s += a[i];
    m = s - m;
    if (m < 0) {
        for (int i = 1; i <= n; ++i) std::cout << 0.0 << std::endl;
        return 0;
    }
    if (n == 1) {
        std::cout << 1.0 << std::endl;
    } else if (n == 2) {
        b[a[1]][a[2]] = 1;
        for (int i = a[1]; i >= 0 && i + a[2] > m; --i) {
            for (int j = a[2]; j >= 0 && i + j > m; --j) {
                if (i) b[i - 1][j] += b[i][j] / ((i > 0) + (j > 0));
                if (j) b[i][j - 1] += b[i][j] / ((i > 0) + (j > 0));
            }
        }
        for (int i = 0; i <= a[1]; ++i) {
            if (m - i < 0 || m - i > a[2]) continue;
            if (i) ans[1] += b[i][m - i];
            if (m - i) ans[2] += b[i][m - i];
        }
        std::cout << ans[1] << std::endl << ans[2] << std::endl;
    } else if (n == 3) {
        c[a[1]][a[2]][a[3]] = 1;
        for (int i = a[1]; i >= 0 && i + a[2] + a[3] > m; --i) {
            for (int j = a[2]; j >= 0 && i + j + a[3] > m; --j) {
                for (int k = a[3]; k >= 0 && i + j + k > m; --k) {
                    x = (i > 0) + (j > 0) + (k > 0);
                    if (i) c[i - 1][j][k] += c[i][j][k] / x;
                    if (j) c[i][j - 1][k] += c[i][j][k] / x;
                    if (k) c[i][j][k - 1] += c[i][j][k] / x;
                }
            }
        }
        for (int i = 0; i <= a[1]; ++i) {
            for (int j = 0; j <= a[2]; ++j) {
                if (m - i - j < 0 || m - i - j > a[3]) continue;
                if (i) ans[1] += c[i][j][m - i - j];
                if (j) ans[2] += c[i][j][m - i - j];
                if (m - i - j) ans[3] += c[i][j][m - i - j];
            }
        }
        std::cout << ans[1] << std::endl
                  << ans[2] << std::endl
                  << ans[3] << std::endl;
    } else {
        d[a[1]][a[2]][a[3]][a[4]] = 1;
        for (int i = a[1]; i >= 0 && i + a[2] + a[3] + a[4] > m; --i) {
            for (int j = a[2]; j >= 0 && i + j + a[3] + a[4] > m; --j) {
                for (int k = a[3]; k >= 0 && i + j + k + a[4] > m; --k) {
                    for (int l = a[4]; l >= 0 && i + j + k + l > m; --l) {
                        x = (i > 0) + (j > 0) + (k > 0) + (l > 0);
                        if (i) d[i - 1][j][k][l] += d[i][j][k][l] / x;
                        if (j) d[i][j - 1][k][l] += d[i][j][k][l] / x;
                        if (k) d[i][j][k - 1][l] += d[i][j][k][l] / x;
                        if (l) d[i][j][k][l - 1] += d[i][j][k][l] / x;
                    }
                }
            }
        }
        for (int i = 0; i <= a[1]; ++i) {
            for (int j = 0; j <= a[2]; ++j) {
                for (int k = 0; k <= a[3]; ++k) {
                    if (m - i - j - k < 0 || m - i - j - k > a[4]) continue;
                    if (i) ans[1] += d[i][j][k][m - i - j - k];
                    if (j) ans[2] += d[i][j][k][m - i - j - k];
                    if (k) ans[3] += d[i][j][k][m - i - j - k];
                    if (m - i - j - k) ans[4] += d[i][j][k][m - i - j - k];
                }
            }
        }
        std::cout << ans[1] << std::endl
                  << ans[2] << std::endl
                  << ans[3] << std::endl
                  << ans[4] << std::endl;
    }
    return 0;
}