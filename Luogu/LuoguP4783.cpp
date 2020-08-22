#include <bits/stdc++.h>
const int N = 1005;
const long long mod = 1000000007;
int n, m;
long long a[N][N];
inline long long power(long long x, long long y) {
    return y ? power(x * x % mod, y / 2) * (y & 1 ? x : 1) % mod : 1;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n;
    m = n * 2;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) std::cin >> a[i][j];
        a[i][i + n] = 1;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            if (a[j][i]) {
                for (int k = 1; k <= m; ++k) std::swap(a[i][k], a[j][k]);
            }
        }
        if (!a[i][i]) std::cout << "No Solution\n", exit(0);
        long long tmp = power(a[i][i], mod - 2);
        for (int j = i; j <= m; ++j) a[i][j] = a[i][j] * tmp % mod;
        for (int j = 1; j <= n; ++j) {
            if (j != i) {
                tmp = a[j][i];
                for (int k = i; k <= m; ++k) {
                    a[j][k] = (a[j][k] - tmp * a[i][k] % mod + mod) % mod;
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = n + 1; j <= m; ++j) {
            std::cout << a[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}