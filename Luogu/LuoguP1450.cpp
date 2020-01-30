#include <bits/stdc++.h>
const int N = 100000;
const int Np = N + 5;
int n, x, y, c;
int a[4], k[4];
long long ans;
long long dp[Np];
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> a[0] >> a[1] >> a[2] >> a[3] >> n;
    dp[0] = 1;
    for (int i = 0; i < 4; ++i) {
        for (int j = a[i]; j <= N; ++j) {
            dp[j] += dp[j - a[i]];
        }
    }
    for (int i = 1; i <= n; ++i) {
        std::cin >> k[0] >> k[1] >> k[2] >> k[3] >> x;
        for (int j = 0; j < 4; ++j) {
            k[j] = a[j] * (k[j] + 1);
        }
        ans = 0;
        for (int j = 0; j < 16; ++j) {
            y = x;
            c = 1;
            for (int l = 0; l < 4; ++l) {
                if (j & (1 << l)) {
                    y -= k[l];
                    c = -c;
                }
            }
            if (y >= 0) {
                ans += c * dp[y];
            }
        }
        std::cout << ans << std::endl;
    }
    return 0;
}