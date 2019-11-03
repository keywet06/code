#include <bits/stdc++.h>
const int N = 105;
const int M = 105;
const int mod = 988244353;
int n, m, k, x, y, z, flag;
int ac[M], oc[M];
int a[M][N], as[M][N], os[M][N];
long long ans, f;
long long power[M];
void Exgcd(long long, long long, long long &, long long &);
long long inv(long long);
long long C(int, int);
void dfs(int);
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
    ac[0] = oc[0] = n;
    power[0] = 1;
    for (int i = 1; i < M; ++i) {
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
inline long long C(int m, int n) {
    return power[m] * inv(power[n] * power[m - n] % mod) % mod;
}
inline void dfs(int now) {
    if (ac[now - 1] < k || oc[now - 1] < k) {
        return;
    }
    if (now == m + 1) {
        if (!flag) {
            flag = 1;
            return;
        }
        (ans += f * C(ac[now - 1], k) * C(oc[now - 1], k) % mod) %= mod;
        return;
    }
    ac[now] = ac[now - 1];
    oc[now] = oc[now - 1];
    for (int i = 1; i <= n; ++i) {
        as[now][i] = as[now - 1][i];
        os[now][i] = os[now - 1][i];
    }
    dfs(now + 1);
    f *= -1;
    ac[now] = oc[now] = 0;
    for (int i = 1; i <= n; ++i) {
        ac[now] += as[now][i] = as[now - 1][i] && a[now][i];
        oc[now] += os[now][i] = os[now - 1][i] && !a[now][i];
    }
    dfs(now + 1);
    ac[now] = oc[now] = 0;
    for (int i = 1; i <= n; ++i) {
        ac[now] += as[now][i] = as[now - 1][i] && !a[now][i];
        oc[now] += os[now][i] = os[now - 1][i] && a[now][i];
    }
    dfs(now + 1);
    f *= -1;
}