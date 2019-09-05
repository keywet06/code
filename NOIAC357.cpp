#include <bits/stdc++.h>
const int N = 1000005;
int n;
int a[N], b[N];
long long ans;
void msort(int, int);
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    msort(1, n);
    printf("%lld\n", ans);
    return 0;
}
inline void msort(int l, int r) {
    if (l == r) {
        return;
    }
    int mid = (l + r) >> 1;
    msort(l, mid);
    msort(mid + 1, r);
    int ls = mid + 1, rs = mid + 1;
    for (int i = l; i <= mid; ++i) {
        while (ls <= r && a[ls] <= 1.1111111112 * a[i]) {
            ++ls;
        }
        while (rs <= r && a[rs] < 0.9 * a[i]) {
            ++rs;
        }
        ans += ls - rs;
    }
    for (int i = l; i <= r; ++i) {
        b[i] = a[i];
    }
    ls = l;
    rs = mid + 1;
    int cnt = l - 1;
    while (ls <= mid && rs <= r) {
        if (b[ls] < b[rs]) {
            a[++cnt] = b[ls++];
        } else {
            a[++cnt] = b[rs++];
        }
    }
    while (ls <= mid) {
        a[++cnt] = b[ls++];
    }
    while (rs <= r) {
        a[++cnt] = b[rs++];
    }
}