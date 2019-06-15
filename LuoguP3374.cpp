#include <bits/stdc++.h>
const int N = 2000005;
long long m, n, o, x, y, z;
long long plus[N], tree[N];
void build(long long, long long, long long);
void plusdown(long long, long long, long long, long long, long long, long long);
void pushdown(long long, long long, long long);
long long query(long long, long long, long long, long long, long long);
int main() {
    scanf("%lld %lld", &n, &m);
    build(1, 1, n);
    while (m--) {
        scanf("%lld", &o);
        if (o == 1) {
            scanf("%lld %lld", &x, &y);
            plusdown(1, 1, n, x, x, y);
        } else {
            scanf("%lld %lld", &x, &y);
            printf("%lld\n", query(1, 1, n, x, y));
        }
    }
    return 0;
}
inline void build(long long v, long long l, long long r) {
    if (l == r) {
        scanf("%lld", &tree[v]);
        return;
    }
    long long mid = (l + r) >> 1;
    build(v << 1, l, mid);
    build(v << 1 | 1, mid + 1, r);
    tree[v] = tree[v << 1] + tree[v << 1 | 1];
}
inline void plusdown(long long v, long long sl, long long sr, long long ul, long long ur, long long x) {
    if (sl == ul && sr == ur) {
        tree[v] += x * (ur - ul + 1);
        plus[v] += x;
    } else {
        pushdown(v, sl, sr);
        long long mid = (sl + sr) >> 1;
        tree[v] += x * (ur - ul + 1);
        if (ul <= mid) {
            plusdown(v << 1, sl, mid, ul, std::min(mid, ur), x);
        }
        if (ur > mid) {
            plusdown(v << 1 | 1, mid + 1, sr, std::max(mid + 1, ul), ur, x);
        }
    }
}
inline void pushdown(long long v, long long l, long long r) {
    long long mid = (l + r) >> 1;
    tree[v << 1] += (mid - l + 1) * plus[v];
    plus[v << 1] += plus[v];
    tree[v << 1 | 1] += (r - mid) * plus[v];
    plus[v << 1 | 1] += plus[v];
    plus[v] = 0;
}
inline long long query(long long v, long long sl, long long sr, long long ul, long long ur) {
    if (sl == ul && sr == ur) {
        return tree[v];
    } else {
        pushdown(v, sl, sr);
        long long mid = (sl + sr) >> 1, tmp = 0;
        if (ul <= mid) {
            tmp += query(v << 1, sl, mid, ul, std::min(mid, ur));
        }
        if (ur > mid) {
            tmp += query(v << 1 | 1, mid + 1, sr, std::max(mid + 1, ul), ur);
        }
        return tmp;
    }
}