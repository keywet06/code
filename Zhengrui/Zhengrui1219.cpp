#include <bits/stdc++.h>
const int N = 100000;
const int Np = N + 5;
const long long mod = 998244353;
long long a, b, m, n, p, x, y;
long long jc[Np], dp[Np], ps[Np], p1s[Np];
long long power(long long, long long);
long long exgcd(long long, long long, long long &, long long &);
long long inv(long long);
long long C(long long, long long);
inline long long power(long long x, long long y) {
    return y ? power(x * x % mod, y / 2) * (y & 1 ? x : 1) % mod : 1;
}
inline long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    long long tmp = exgcd(b, a % b, x, y);
    std::swap(x, y);
    y = y - x * (a / b);
    return tmp;
}
inline long long inv(long long a) {
    long long x, y;
    exgcd(a, mod, x, y);
    return (x % mod + mod) % mod;
}
inline long long C(long long m, long long n) {
    return jc[m] * inv(jc[m - n] * jc[n] % mod) % mod;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> x >> y;
    p = x * inv(y) % mod;
    jc[0] = ps[0] = p1s[0] = 1;
    for (int i = 1; i <= n; ++i) {
        jc[i] = jc[i - 1] * i % mod;
        ps[i] = ps[i - 1] * p % mod;
        p1s[i] = p1s[i - 1] * (mod + 1 - p) % mod;
    }
    for (int i = 2; i <= n; ++i) {
        dp[i] = 1;
        for (int j = 1; j < i; ++j) {
            dp[i] = (dp[i] + dp[j] * p1s[i - j] % mod * ps[j] % mod * C(i, j)) %
                    mod;
        }
        dp[i] = (dp[i] * inv((mod * 2 + 1 - ps[i] - p1s[i]) % mod)) % mod;
    }
    std::cout << dp[n] << std::endl;
    return 0;
}