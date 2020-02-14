#include <bits/stdc++.h>
const int K = 1000000;
const int Ki = 10;
const int Kip = Ki + 1;
const int N = 2000;
const int Np = N + 1;
const int Ni = 10;
const int Nip = Ni + 1;
const int mod = 998244353;
int ans, n, m, k;
int sum[Np][Np];
int dp[Kip][Nip][Nip][Nip][Nip];
std::string s;
int sju(const int xl, const int xr, const int yl, const int yr);
inline int sju(const int xl, const int xr, const int yl, const int yr) {
    return sum[xr][yr] - sum[xr][yl - 1] - sum[xl - 1][yr] +
           sum[xl - 1][yl - 1];
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) {
        std::cin >> s;
        for (int j = 1; j <= m; ++j) {
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] +
                        (s[j - 1] == '0');
        }
    }
    dp[0][1][n][1][m] = 1;
    for (int i = 0; i < k; ++i) {
        for (int xl = 1; xl <= n; ++xl) {
            for (int xr = xl; xr <= n; ++xr) {
                for (int yl = 1; yl <= m; ++yl) {
                    for (int yr = yl; yr <= m; ++yr) {
                        if (!dp[i][xl][xr][yl][yr]) {
                            continue;
                        }
                        for (int nxl = 1; nxl <= xr; ++nxl) {
                            for (int nxr = std::max(nxl, xl); nxr <= n; ++nxr) {
                                for (int nyl = 1; nyl <= yr; ++nyl) {
                                    for (int nyr = std::max(nyl, yl); nyr <= m;
                                         ++nyr) {
                                        if (sju(nxl, nxr, nyl, nyr)) {
                                            continue;
                                        }
                                        (dp[i + 1][std::max(xl, nxl)][std::min(
                                             xr, nxr)][std::max(yl, nyl)]
                                           [std::min(yr, nyr)] +=
                                         dp[i][xl][xr][yl][yr]) %= mod;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for (int xl = 1; xl <= n; ++xl) {
        for (int xr = xl; xr <= n; ++xr) {
            for (int yl = 1; yl <= m; ++yl) {
                for (int yr = yl; yr <= m; ++yr) {
                    (ans += dp[k][xl][xr][yl][yr]) %= mod;
                }
            }
        }
    }
    std::cout << ans << std::endl;
    return 0;
}