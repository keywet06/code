#include <bits/stdc++.h>
const int N = 20050;
long long T, n, max;
long long a[N], f[N];
int Main();
int main() {
    scanf("%d", &T);
    while (T--) {
        Main();
    }
    return 0;
}
int Main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    memset(f, 0, sizeof(f));
    max = 0;
    for (int i = 1; i <= 7; ++i) {
        max = std::max(max, a[i]);
        f[i] = max * 7;
    }
    for (int i = 7; i <= n; ++i) {
        f[i] = std::max(f[i - 1], f[i - 7] + a[i] * 7);
    }
    printf("%lld\n", f[n]);
    return 0;
}