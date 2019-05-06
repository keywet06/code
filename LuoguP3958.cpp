#include <bits/stdc++.h>
const long long N = 1005;
const long long M = N * N;
long long T, cnt, n, h, r;
long long a[N], head[N], x[N], y[N], z[N];
long long next[M], to[M];
long long sqr(long long);
void insert2(long long, long long);
void insert(long long, long long);
long long dfs(long long);
void Main();
int main() {
    scanf("%lld", &T);
    while (T--) {
        Main();
        memset(head, 0, sizeof(head));
        memset(a, 0, sizeof(a));
    }
    return 0;
}
inline void Main() {
    scanf("%lld %lld %lld", &n, &h, &r);
    for (long long i = 1; i <= n; ++i) {
        scanf("%lld %lld %lld", &x[i], &y[i], &z[i]);
        if (std::abs(z[i]) <= r) {
            insert2(i, n + 1);
        }
        if (std::abs(z[i] - h) <= r) {
            insert2(i, n + 2);
        }
    }
    r *= 2;
    r *= r;
    for (long long i = 1; i < n; ++i) {
        for (long long j = i + 1; j <= n; ++j) {
            if (sqr(x[i] - x[j]) + sqr(y[i] - y[j]) + sqr(z[i] - z[j]) <= r) {
                insert2(i, j);
            }
        }
    }
    if (dfs(n + 1)) {
        puts("Yes");
    } else {
        puts("No");
    }
}
inline long long sqr(long long x) { return x * x; }
inline void insert2(long long a, long long b) {
    insert(a, b);
    insert(b, a);
}
inline void insert(long long a, long long b) {
    ++cnt;
    next[cnt] = head[a];
    head[a] = cnt;
    to[cnt] = b;
}
inline long long dfs(long long u) {
    if (u == n + 2) {
        return 1;
    }
    a[u] = 1;
    for (long long v = head[u]; v; v = next[v]) {
        if (!a[to[v]] && dfs(to[v])) {
            return 1;
        }
    }
    return 0;
}