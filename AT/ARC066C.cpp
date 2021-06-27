#include <bits/stdc++.h>

using int64 = long long;

inline void ios() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
}

const int C = 3;
const int N = 100005;
const int64 linf = 1ll << 50;

int n;

int64 a[N];
int64 dp[N][C];

std::string s;

inline int64 maxs(int64 a, int64 b, int64 c) {
    return std::max(a, std::max(b, c));
}

int main() {
    ios();
    std::cin >> n;
    std::cin >> a[1];
    for (int i = 2; i <= n; ++i) {
        std::cin >> s >> a[i];
        a[i] = s[0] == '+' ? a[i] : -a[i];
    }
    dp[1][0] = a[1], dp[1][1] = dp[1][2] = -linf;
    for (int i = 2; i <= n + 1; ++i) {
        dp[i][0] = maxs(dp[i - 1][0], dp[i - 1][1], dp[i - 2][2]) + a[i];
        dp[i][1] = a[i] > 0 ? std::max(dp[i - 1][1] - a[i], dp[i - 1][2] - a[i])
                            : maxs(dp[i - 1][0] + a[i], dp[i - 1][1] - a[i],
                                   dp[i - 1][2] - a[i]);
        dp[i][2] = a[i] > 0
                       ? dp[i - 1][2] + a[i]
                       : std::max(dp[i - 1][2] + a[i], dp[i - 1][1] - a[i]);
        std::cout << dp[i][0] << ' ' << dp[i][1] << ' ' << dp[i][2]
                  << std::endl;
    }
    std::cout << dp[n + 1][0] << std::endl;
    return 0;
}