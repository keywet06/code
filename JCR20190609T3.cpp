#include <bits/stdc++.h>
const int N = 100000;
int ans, n, now, s;
int a[N];
int main() {
    freopen("costume.in", "r", stdin);
    freopen("costume.out", "w", stdout);
    scanf("%d %d", &n, &s);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    std::sort(a + 1, a + n + 1);
    now = n;
    for (int i = 1; i <= n; ++i) {
        while (now && a[i] + a[now] > s) {
            --now;
        }
        ans += now;
        if (i <= now) {
            --ans;
        }
    }
    printf("%d\n", ans / 2);
    return 0;
}