#include <bits/stdc++.h>
const long long C = 10;
const long long N = 3000000;
const long long INF = (1 << 30) - 1;
const long long mod = 12345678;
const long long a1 = 233;
const long long a2 = 12345446;
long long S, m, n, x;
long long vis[C], d[C], ans[C];
long long dp_1[N], dp_2[N];
long long *dp1 = dp_1, *dp2 = dp_2;
void memset(long long, long long);
long long swap(long long, long long, long long);
long long bi(long long, long long, long long);
void dfs(long long, long long, long long, long long);
void getans(long long, long long);
int main() {
    scanf("%lld %lld", &n, &m);
    for (long long i = 0; i < n; ++i) {
        scanf("%lld", &x);
        S |= x << (3 * i);
    }
    dp1[S] = 1;
    for (long long i = 1; i <= m; ++i) {
        std::swap(dp1, dp2);
        memset(i, 0);
        for (long long j = 2; j <= n; ++j) {
            dfs(1, j - 1, j, 0);
        }
    }
    getans(1, 0);
    for (long long i = 1; i <= n; ++i) {
        printf("%lld ", ans[i]);
    }
    return 0;
}
inline void memset(long long v, long long x) {
    if (v > n) {
        dp1[x] = 0;
        return;
    }
    for (long long i = 1; i <= n; ++i) {
        if (!vis[i]) {
            ++vis[i];
            memset(v + 1, x | (i << ((v - 1) * 3)));
            --vis[i];
        }
    }
}
inline long long swap(long long S, long long x, long long y) {
    long long tmpa, tmpb, tmpc;
    tmpa = (S & (3 << (3 * x - 3))) >> (3 * x - 3);
    tmpb = (S & (3 << (3 * y - 3))) >> (3 * y - 3);
    tmpc = S & (INF ^ (tmpa << (3 * x - 3)) ^ (tmpb << (3 * y - 3)));
    // printf("swap(%d, %d, %d) = %d;\n", S, x, y, tmpc ^ (tmpa << (3 * y - 3)) ^ (tmpb << (3 * x - 3)));
    return tmpc ^ (tmpa << (3 * y - 3)) ^ (tmpb << (3 * x - 3));
}
inline long long bi(long long S, long long x, long long y) {
    return (((S & (3 << (3 * x - 3))) >> (3 * x - 3)) < ((S & (3 << (3 * y - 3))) >> (3 * y - 3))) ? a1 : a2;
}
inline void dfs(long long v, long long x, long long y, long long S) {
    if (v > n) {
        (dp1[swap(S, x, y)] += dp2[S] * bi(S, x, y)) %= mod;
        (dp1[S] += dp2[S] * bi(S, y, x)) %= mod;
        return;
    }
    for (long long i = 1; i <= n; ++i) {
        if (!vis[i]) {
            ++vis[i];
            dfs(v + 1, x, y, x | (i << ((v - 1) * 3)));
            --vis[i];
        }
    }
}
inline void getans(long long v, long long S) {
    if (v > n) {
        for (long long i = 1; i <= n; ++i) {
            (ans[d[i]] += d[i] * dp1[S]) % mod;
        }
        return;
    }
    for (long long i = 1; i <= n; ++i) {
        if (!vis[i]) {
            ++vis[i];
            d[v] = i;
            getans(v + 1, x | (i << ((v - 1) * 3)));
            --vis[i];
        }
    }
}