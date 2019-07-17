#include <bits/stdc++.h>
const int C = 25;
long long k, now, n;
long long co[C], f[C], ans[C];
int main() {
    scanf("%lld", &k);
    co[0] = 1;
    for (int i = 1; i <= 18; ++i) {
        co[i] = co[i - 1] * 10;
        f[i] = f[i - 1] * 8 + co[i - 1] * 2;
    }
    f[19] = 1e18 + 1;
    while (f[now + 1] < k) {
        ++now;
    }
    n = now;
    while (~now) {
        while (f[now] >= k) {
            --now;
        }
        if (ans[now] == 3 || ans[now] == 6) {
            if (k <= co[now] + f[now]) {
                k -= f[now] + 1;
                ++ans[now];
                for (int i = n; i >= now; --i) {
                    printf("%d", ans[i]);
                }
                for (int i = now - 1; ~i; --i) {
                    printf("%d", k / co[i] % 10);
                }
                printf("\n");
                return 0;
            } else {
                ++ans[now];
                k -= co[now];
            }
        } else {
            ++ans[now];
            k -= f[now];
        }
    }
    for (int i = n; ~i; --i) {
        printf("%d", ans[i]);
    }
    printf("\n");
    return 0;
}