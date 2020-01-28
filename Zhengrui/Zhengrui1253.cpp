#include <bits/stdc++.h>
const int N = 5005;
int n, q, k;
int dp[N][N][2];
std::string is;
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> q;
    std::cin >> is;
    is = " " + is;
    for (int i = 1; i <= n; ++i) {
        dp[i][1][1] = -(dp[i][1][0] = is[i] == '1');
        dp[n][i][1] = -(dp[n][i][0] = is[n] == '1');
    }
    for (int i = n - 1; i; --i) {
        for (int j = 2; j <= n; ++j) {
            dp[i][j][0] = std::max(dp[i + 1][j - 1][1] + (is[i] == '1'),
              std::min(dp[i + 1][j - 1][0] - (is[i] == '1'), dp[i + 1][j][0]));
            dp[i][j][1] = std::min(dp[i + 1][j - 1][0] - (is[i] == '1'),
              std::max(dp[i + 1][j - 1][1] + (is[i] == '1'), dp[i + 1][j][1]));
        }
    }
    for (int i = 1; i <= q; ++i) {
        std::cin >> k;
        std::cout << dp[1][k][0] << std::endl;
    }
    return 0;
}