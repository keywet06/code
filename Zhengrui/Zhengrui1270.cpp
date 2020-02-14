#include <bits/stdc++.h>
const int mod = 1000000007;
const int N = 5000;
const int Np = N + 5;
int n;
long long dp[Np];
int main() {
    std::cin >> n;
    dp[0] = 1;
    dp[1] = 1;
    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j < n; ++j) {
            (dp[i] += dp[j] * dp[n - 1 - j]) %= mod;
        }
    }
    std::cout << dp[n] << std::endl;
    return 0;
}