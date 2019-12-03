#include <bits/stdc++.h>
const int N = 200005;
int ans, l, s, t, m;
int a[N], c[N], is[N], dp[N];
int main() {
    scanf("%d %d %d %d", &l, &s, &t, &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%d", &a[i]);
    }
    std::sort(a + 1, a + m + 1);
    if (s == t) {
        for (int i = 1; i <= m; ++i) {
            ans += a[i] % s == 0;
        }
        printf("%d\n", ans);
        return 0;
    }
    a[m + 1] = l;
    for (int i = 1; i <= m + 1; ++i) {
        c[i] = a[i] - a[i - 1] > 200 ? c[i - 1] + 200 : c[i - 1] + a[i] - a[i - 1];
        is[c[i]] = 1;
    }
    l = c[m + 1] + 100;
    is[c[m + 1]] = 0;
    memset(dp, 100, sizeof(dp));
    dp[0] = 0;
    for (int i = 0; i <= l; ++i) {
        for (int j = s; j <= t; ++j) {
            dp[i + j] = std::min(dp[i + j], dp[i] + is[i]);
        }
    }
    ans = 1e9;
    for (int i = c[m + 1]; i <= l; ++i) {
        ans = std::min(ans, dp[i]);
    }
    printf("%d\n", ans);
    return 0;
}