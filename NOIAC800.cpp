#include <bits/stdc++.h>
const int N = 1000005;
int n;
int vis[N];
long long max, min;
long long p[N], r[N];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld %lld", &p[i], &r[i]);
    }
    max = p[1] + r[1];
    for (int i = 2; i < n; ++i) {
        if (p[i] > max) {
            printf("-1\n");
            return 0;
        }
        max = std::max(max, p[i] + r[i]);
    }
    min = p[n] - r[n];
    for (int i = n - 1; i; --i) {
        if (p[i] < min) {
            printf("-1\n");
            return 0;
        }
        min = std::min(min, p[i] - r[i]);
    }
    printf("%lld\n", (p[n] - p[1]) * 3);
    return 0;
}