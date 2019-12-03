#include <bits/stdc++.h>
const int N = 1000005;
const int mod = 100000007;
int n, q;
long long ans, x, y;
long long a[N];
long long fastmi(long long, long long);
long long ni(long long);
int main() {
    scanf("%d %d", &n, &q);
    a[0] = 1;
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
        (a[i] *= a[i - 1]) %= mod;
    }
    for (int i = 1; i <= q; ++i) {
        scanf("%lld %lld", &x, &y);
        ans = 0;
        for (int l = x; l <= y; ++l) {
            for (int r = l; r <= y; ++r) {
                (ans += a[r] * ni(a[l - 1])) %= mod;
            }
        }
        (ans *= ni((y - x + 1) * (y - x + 2) / 2 % mod)) %= mod;
        printf("%lld\n", ans);
    }
    return 0;
}
inline long long fastmi(long long a, long long b) {
    if (b == 1) {
        return a;
    }
    return (fastmi(a * a % mod, b / 2) * (b & 1 ? a : 1)) % mod;
}
inline long long ni(long long x) {
    return fastmi(x, mod - 2);
}