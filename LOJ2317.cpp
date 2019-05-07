#include <bits/stdc++.h>
#include <cmath>
const int M = 1000005;
const int N = 1005;
long long T, cnt, n, h, r, f;
long long sta[N], head[N], x[N], y[N], z[N];
long long next[M], to[M];
void init();
void Main();
void insert(int, int);
void insert2(int, int);
long long sqr(long long);
void dfs(int);
int main() {
    scanf("%lld", &T);
    while (T--) {
        init();
        Main();
    }
    return 0;
}
inline void init() {
    cnt = 0;
    memset(sta, 0, sizeof(sta));
    memset(head, 0, sizeof(head));
}
inline void Main() {
    scanf("%lld %lld %lld", &n, &h, &r);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld %lld %lld", &x[i], &y[i], &z[i]);
        if (z[i] <= r) {
            insert(1, i + 1);
        }
        if (z[i] >= h - r) {
            insert(i + 1, n + 2);
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (sqr(x[i] - x[j]) + sqr(y[i] - y[j]) + sqr(z[i] - z[j]) <= sqr(2 * r)) {
                insert(i + 1, j + 1);
            }
        }
    }
    f = 0;
    dfs(1);
    if (f) {
        puts("Yes");
    } else {
        puts("No");
    }
}
inline void insert(int x, int y) {
    insert2(x, y);
    insert2(y, x);
}
inline void insert2(int x, int y) {
    ++cnt;
    next[cnt] = head[x];
    head[x] = cnt;
    to[cnt] = y;
}
inline long long sqr(long long x) {
    return x * x;
}
inline void dfs(int x) {
    if (f) {
        return;
    }
    if (x == n + 2) {
        f = 1;
        return;
    }
    sta[x] = 1;
    for (int i = head[x]; i; i = next[i]) {
        if (!sta[to[i]]) {
            dfs(to[i]);
        }
    }
}
