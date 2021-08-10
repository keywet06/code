#include <bits/stdc++.h>

const int N = 2005;

int n, ans;
int a[N];
int dp[N][N];

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    dp[1][1] = 0;
    for (int i = 2; i <= n; ++i) {
        dp[i][i] = dp[i - 1][i - 1] + std::abs(a[i - 1] - a[i]);
        for (int j = 1; j <= i - 2; ++j) {
            dp[i][i] =
                std::min(dp[i][i], dp[i - 1][j] + std::abs(a[j] - a[i - 1]) +
                                       std::abs(a[j] - a[i]));
            dp[i][j] = dp[i - 1][j] + std::abs(a[i] - a[i - 1]);
        }
        dp[i][i - 1] =
            i == 2 ? 0 : dp[i - 2][i - 2] + std::abs(a[i - 2] - a[i]);
        for (int j = 1; j <= i - 3; ++j) {
            dp[i][i - 1] = std::min(dp[i][i - 1],
                                    dp[i - 2][j] + std::abs(a[i - 2] - a[j]) +
                                        std::abs(a[j] - a[i]));
        }
    }
    ans = dp[n][n];
    for (int i = 1; i < n; ++i) {
        ans = std::min(ans, dp[n][i] + std::abs(a[n] - a[i]));
    }
    std::cout << ans << std::endl;
    return 0;
}