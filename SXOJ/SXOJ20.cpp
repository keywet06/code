#include <bits/stdc++.h>

using int64 = long long;

const int P = 998244353;
const int I2 = (P + 1) / 2;
const int N = 3005;

int n;

int64 x;
int64 dp[N][N];

inline int64 power(int64 x, int y) {
    int64 ret = 1;
    while (y) ret = y & 1 ? ret * x % P : ret, x = x * x % P, y >>= 1;
    return ret;
}

inline int64 inv(int64 x) { return power(x, P - 2); }

inline int64 C2(int64 x) { return x * (x - 1) % P * I2 % P; }

inline int64 IC2(int64 x) { return inv(C2(x)); }

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int i = 2; i <= n; ++i) {
        x = IC2(i);
        for (int j = i; ~j; --j) {
            if (j >= 2) {
                dp[i - j][j] += C2(j) * (dp[i - j][j - 2] + 1) % P * x % P;
            }
            if (i - j >= 2) {
                dp[i - j][j] +=
                    C2(i - j) * (dp[i - j - 2][j + 2] + 1) % P * x % P;
            }
            if (j && i - j) {
                dp[i - j][j] +=
                    j * (i - j) * (dp[i - j - 1][j] + 1) % P * x % P;
            }
            dp[i - j][j] %= P;
        }
    }
    std::cout << dp[n][0] << std::endl;
    return 0;
}