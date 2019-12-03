#include <bits/stdc++.h>
const int N = 100005;
int ans, m, n, now, x, y;
int a[N], b[N];
int main() {
    freopen("match.in", "r", stdin);
    freopen("match.out", "w", stdout);
    scanf("%d %d %d %d", &n, &m, &x, &y);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d", &b[i]);
    }
    now = 1;
    for (int i = 1; i <= n; ++i) {
        while (now < n && b[now] < a[i] - x) {
            ++now;
        }
        if (a[i] - x <= b[now] && b[now] <= a[i] + y) {
            ++ans;
            ++now;
        }
        if (now > n) {
            break;
        }
    }
    printf("%d\n", ans);
    return 0;
}