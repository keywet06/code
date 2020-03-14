#include <bits/stdc++.h>
const int B = 2;
const int N = 200005;
const int M = 21;
int cas, x, n;
int dp[N][M][B];
std::string s, t;
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> cas;
    while (cas--) {
        std::cin >> x >> s >> t;
        memset(dp, 0, sizeof(dp));
        n = s.size();
        s = " " + s;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= x; ++j) {
                dp[i][j][0] = std::max(dp[i - 1][j][1], dp[i - 1][j][0]);
                dp[i][j][1] = std::max(dp[i - 1][j - 1][0], dp[i - 1][j][1]);
            }
        }
    }
    return 0;
}