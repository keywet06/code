#include <bits/stdc++.h>
const int N = 105;
const long long mod = 998244353;
long long n, m, k, x, y, z, flag;
long long ans, f;
long long power[N];
std::bitset<N> a[N], as[N], os[N];
void Exgcd(long long, long long, long long &, long long &);
long long inv(long long);
long long C(long long, long long);
void dfs(long long);
int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= m; ++i) {
        scanf("%d", &x);
        for (int j = 1; j <= x; ++j) {
            scanf("%d", &y);
            a[i][y] = 1;
        }
    }
    for (int i = 1; i <= n; ++i) {
        as[0][i] = os[0][i] = 1;
    }
    power[0] = 1;
    for (int i = 1; i < N; ++i) {
        (power[i] = power[i - 1] * i) %= mod;
    }
    f = -1;
    dfs(1);
    printf("%lld\n", (ans + mod) % mod);
    return 0;
}
inline void Exgcd(long long a, long long b, long long &x, long long &y) {
    if (!b) {
        x = 1;
        y = 0;
    } else {
        Exgcd(b, a % b, y, x);
        y -= a / b * x;
    }
}
inline long long inv(long long a) {
    long long x, y;
    Exgcd(a, mod, x, y);
    return (x % mod + mod) % mod;
}
inline long long C(long long m, long long n) {
    return power[m] * inv(power[n] * power[m - n] % mod) % mod;
}
inline void dfs(long long now) { 
    if (as[now - 1].count() < k || os[now - 1].count() < k) {
        return;
    }
    if (now == m + 1) {
        if (!flag) {
            flag = 1;
            return;
        }
        (ans += f * C(as[now - 1].count(), k) * C(os[now - 1].count(), k) %
                mod) %= mod;
        return;
    }
    as[now] = as[now - 1];
    os[now] = os[now - 1];
    dfs(now + 1);
    f *= -1;
    as[now] = as[now - 1] & a[now];
    os[now] = os[now - 1] & ~a[now];
    dfs(now + 1);
    as[now] = as[now - 1] & ~a[now];
    os[now] = os[now - 1] & a[now];
    dfs(now + 1);
    f *= -1;
}