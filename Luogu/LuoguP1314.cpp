#include <bits/stdc++.h>
const int N = 200005;
int n, m;
int ql[N], qr[N];
long long S, l, r, mid, tmp;
long long w[N], v[N], qw[N], qv[N];
long long check(long long);
int main() {
    scanf("%d %d %lld", &n, &m, &S);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld %lld", &w[i], &v[i]);
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d", &ql[i], &qr[i]);
    }
    l = 1;
    r = 1000001;
    while (l < r) {
        mid = l + r + 1 >> 1;
        if (check(mid) > S) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    printf("%lld\n", std::min(std::abs(check(l) - S), std::abs(check(l + 1) - S)));
    return 0;
}
inline long long check(long long x) {
    for (int i = 1; i <= n; ++i) {
        qw[i] = qw[i - 1] + (w[i] >= x);
        qv[i] = qv[i - 1] + (w[i] >= x) * v[i];
    }
    tmp = 0;
    for (int i = 1; i <= m; ++i) {
        tmp += (qw[qr[i]] - qw[ql[i] - 1]) * (qv[qr[i]] - qv[ql[i] - 1]);
    }
    return tmp;
}