#include <bits/stdc++.h>
const int N = 200005;
int ans, n, m, l, r, mid;
int s[N];
long long x, y, z;
long long R[N];
template <typename Type>
Type sqrt(Type);
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld %lld", &R[i], &s[i]);
        s[i] += s[i - 1];
    }
    R[n + 1] = 1e9;
    s[n + 1] = s[n];
    for (int i = 1; i <= m; ++i) {
        scanf("%lld %lld %lld", &x, &y, &z);
        x = sqrt(x) + sqrt(y);
        ans = 0;
        l = 1;
        r = n + 1;
        while (l < r) {
            mid = (l + r) >> 1;
            if (sqrt(R[mid] - z) < x || R[mid] < z) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        ans += s[l];
        l = 1;
        r = n + 1;
        while (l < r) {
            mid = (l + r) >> 1;
            if (sqrt(R[mid] + z) <= x) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        ans -= s[l - 1];
        printf("%d\n", ans);
    }
    return 0;
}
template <typename Type>
inline Type sqrt(Type x) {
    return x * x;
}