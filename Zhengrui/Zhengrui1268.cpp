#include <bits/stdc++.h>

const int B = 2;
const int Ba = 1000000000;
const int N = 100000;
const int Np = N + 5;
const int mod = 998244353;

namespace Subtask1 {
long long its(int, int);
int main();
} // namespace Subtask1

int n;
long long ans;
long long dp[Np];
long long b[Np][B][B];

namespace Subtask1 {
inline long long its(int x, int y) {
    return std::max(std::min(b[x][0][1], b[y][0][1]) -
                    std::max(b[x][0][0], b[y][0][0]) + 1, 0ll) *
           std::max(std::min(b[x][1][1], b[y][1][1] -
                    std::max(b[x][1][0], b[y][1][0]) + 1), 0ll) % mod;
}
inline int main() {
    for (int i = 1; i <= n; ++i) {
        dp[i] = 1;
        for (int j = 1; j < i; ++j) {
            (dp[i] += dp[j] * its(i, j)) %= mod;
        }
        (ans += dp[i]) %= mod;
    }
    std::cout << ans << std::endl;
    return 0;
}
} // namespace Subtask1

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> b[i][0][0] >> b[i][1][0] >> b[i][0][1] >> b[i][1][1];
    }
    // if (n <= 1000) {
        return Subtask1::main();
    // }
    return 0;
}