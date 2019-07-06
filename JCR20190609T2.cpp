#include <bits/stdc++.h>
const int N = 20000;
int m, n, x;
int a[N], f[N];
int main() {
    freopen("cowrun.in", "r", stdin);
    freopen("cowrun.out", "w", stdout);
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &x);
        for (int j = m; j; --j) {
            f[j] = f[j - 1] + x;
        }
        f[0] = a[i];
        for (int j = 1; j <= m; ++j) {
            a[i + j] = std::max(a[i + j], f[j]);
        }
        a[i + 1] = std::max(a[i + 1], f[0]);
    }
    printf("%d\n", f[0]);
    return 0;
}