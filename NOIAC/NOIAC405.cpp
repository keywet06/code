#include <bits/stdc++.h>
const long long mod = 1e6 + 3;
int T, x, y, z;
long long mi[mod + 5];
long long power(long long, long long);
long long inv(long long);
long long C(int, int);
long long lucas(int, int);
int main() {
    scanf("%d", &T);
    mi[0] = 1;
    for (int i = 1; i <= mod; ++i) {
        mi[i] = mi[i - 1] * i % mod;
    }
    while (T--) {
        scanf("%d %d %d", &x, &y, &z);
        printf("%lld\n", (lucas(x + z - y + 1, x) - 1 + mod) % mod);
    }
    return 0;
}
inline long long power(long long a, long long b) {
    return b ? (b & 1 ? power(a * a % mod, b / 2) * a % mod : power(a * a % mod, b / 2)) : 1;
}
inline long long inv(long long a) {
    return power(a, mod - 2);
}
inline long long C(int m, int n) {
    return m >= n && n >= 0 ? mi[m] * inv(mi[m - n] * mi[n] % mod) % mod : 0;
}
inline long long lucas(int m, int n) {
    long long res = 1;
    while (m && n) {
        (res *= C(m % mod, n % mod)) %= mod;
        m /= mod;
        n /= mod;
    }
    return res;
}
