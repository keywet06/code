#include <bits/stdc++.h>
const int B = 2;
const int N = 20;
long long n, x, r, t;
long long c[N], dp[N][B];
std::string f;
int main() {
    std::cin >> f >> n;
    for (int i = 1; i <= n; ++i) std::cin >> x, c[x] = 1;
    for (int i = 0; i < f.size(); ++i) {
        for (int j = 1; j < (i ? 10 : f[i] - '0'); ++j) {
            dp[i + 1][0] += !c[j];
        }
        if (!i) dp[i + 1][1] += !c[f[i] - '0'];
        for (int j = 0; j < f[i] - '0'; ++j) {
            dp[i + 1][0] += !c[j] * dp[i][1];
        }
        dp[i + 1][1] += !c[f[i] - '0'] * dp[i][1];
        for (int j = 0; j < 10; ++j) dp[i + 1][0] += !c[j] * dp[i][0];
    }
    std::cout << dp[f.size()][0] + dp[f.size()][1] << std::endl;
    return 0;
}