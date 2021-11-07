#include <bits/stdc++.h>

const int N = 75;
const int M = 155;

int n, m, ans;
int a[N];
int f[N][N][M];

template <typename _Tp>
inline _Tp &mid(_Tp &x, _Tp y) {
    return x = std::min(x, y);
}

template <typename _Tp>
inline _Tp &mad(_Tp &x, _Tp y) {
    return x = std::max(x, y);
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> a[i], mad(m, a[i]);
    memset(f, 63, sizeof(f));
    for (int i = 1; i <= n; ++i) {
        for (int j = a[i] >> 1; j <= m; ++j) f[i][i][j] = std::max(j * 2, a[i]);
    }
    for (int c = 2; c <= n; ++c) {
        for (int l = 1, r = l + c - 1; r <= n; ++l, ++r) {
            for (int k = a[r] >> 1; k <= m; ++k) {
                for (int p = a[r - 1] >> 1; p <= m; ++p) {
                    mid(f[l][r][k], f[l][r - 1][p] +
                                        std::max(0, std::max(2 * k, a[r]) - p));
                }
                for (int x = l; x < r; ++x) {
                    for (int p = a[x] >> 1; p <= k; ++p) {
                        mid(f[l][r][k], f[l][x][p] + f[x + 1][r][k - p]);
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        ans = 0x7fffffff;
        for (int j = 0; j <= m; ++j) mid(ans, f[1][i][j]);
        std::cout << ans << " \n"[i == n];
    }
    return 0;
}