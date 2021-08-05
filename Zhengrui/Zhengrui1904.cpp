#include <bits/stdc++.h>

using int64 = long long;

const int64 P = 1000000007;
const int64 I = (P + 1) >> 1;
const int N = 10000005;
const int N2 = 3005;

int T, n, m;

int64 ans;
int64 r2[N], ct[N], e2[N];
int64 dp[N2][N2];

inline int64 power(int64 x, int64 y) {
    return y ? power(x * x % P, y / 2) * (y & 1 ? x : 1) % P : 1;
}

inline int64 num(int64 x) { return power(2, x * (x - 1) / 2); }

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> T;
    r2[0] = 1;
    for (int i = 1; i < N; ++i) r2[i] = r2[i - 1] * 2 % P;
    e2[0] = 1;
    for (int i = 1; i < N; ++i) e2[i] = e2[i - 1] * I % P;
    ct[0] = 1;
    for (int i = 1; i < N; ++i) ct[i] = ct[i - 1] * (r2[i] - 1) % P;
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        dp[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            dp[i][j] = dp[i - 1][j - 1] * (r2[i] - r2[j - 1]);
            dp[i][j] = (dp[i][j] + dp[i - 1][j] * r2[j]) % P;
        }
    }
    while (T--) {
        std::cin >> n >> m;
        if (n == m) {
            std::cout << ct[n] * num(n) % P << '\n';
            continue;
        }
        std::cout << (dp[n][m] * num(n) + P) % P << '\n';
    }
    return 0;
}