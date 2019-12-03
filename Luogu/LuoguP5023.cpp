#include <bits/stdc++.h>
const long long mod = 1e9 + 7;
long long m, n;
long long power(long long, int);
long long inv(long long);
int main() {
    scanf("%lld %lld", &n, &m);
    if (n > m) {
        std::swap(n, m);
    }
    if (n == 1) {
        printf("%lld\n", power(2, m));
    } else if (n == 2) {
        printf("%lld\n", 4 * power(3, m - 1) % mod);
    } else if (n == 3) {
        printf("%lld\n", 112 * power(3, m - 3) % mod);
    } else {
        if (n == m) {
            printf("%lld\n", (83 * power(8, n) + 5 * power(2, n + 7)) % mod * inv(384) % mod);
        } else {
            printf("%lld\n", (83 * power(8, n) + power(2, n + 8)) % mod * inv(128) % mod * power(3, m - n - 1) % mod);
        }
    }
    return 0;
}
inline long long power(long long x, int y) {
    return y ? power(x * x % mod, y / 2) * (y & 1 ? x : 1) % mod : 1;
}
inline long long inv(long long x) {
    return power(x, mod - 2);
}