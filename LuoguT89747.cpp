#include <bits/stdc++.h>
const int N = 100005;
long long cnt, ans, n, m, x, y;
long long a[N], b[N];
int main() {
    scanf("%lld %lld", &n, &m);
    for (long long i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
    }
    for (long long i = 1; i <= m; ++i) {
        scanf("%lld %lld", &x, &y);
        for (long long j = x; j <= y; ++j) {
            b[j] = a[j];
        }
        std::sort(b + x, b + y + 1);
        ans = 0;
        b[x - 1] = -1;
        for (long long j = x; j <= y; ++j) {
            ans += b[j] * (b[j] != b[j - 1] ? cnt = j : cnt);
        }
        printf("%lld\n", ans);
    }
    return 0;
}