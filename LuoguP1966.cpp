#include <bits/stdc++.h>
const int N = 100005;
int n;
int a[N], b[N], qa[N], qb[N], f[N];
int cmp1(int, int);
int cmp2(int, int);
long long nis(int, int);
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        qa[i] = i;
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &b[i]);
        qb[i] = i;
    }
    std::sort(qa + 1, qa + n + 1, cmp1);
    std::sort(qb + 1, qb + n + 1, cmp2);
    for (int i = 1; i <= n; ++i) {
        f[qa[i]] = qb[i];
    }
    printf("%lld\n", nis(1, n));
    return 0;
}
inline int cmp1(int x, int y) {
    return a[x] < a[y];
}
inline int cmp2(int x, int y) {
    return b[x] < b[y];
}
inline long long nis(int l, int r) {
    if (l >= r) {
        return 0;
    }
    int mid = l + r >> 1, ans = 0;
    ans = nis(l, mid) + nis(mid + 1, r);
    for (int i = l; i <= r; ++i) {
        a[i] = f[i];
    }
    int al = l, bl = mid + 1, k = l;
    while (al <= mid && bl <= r) {
        if (a[al] < a[bl]) {
            f[k++] = a[al++];
        } else {
            ans += mid - al + 1;
            f[k++] = a[bl++];
        }
    }
    while (al <= mid) {
        f[k++] = a[al++];
    }
    while (bl <= r) {
        f[k++] = a[bl++];
    }
    return ans % 99999997;
}
