#include <bits/stdc++.h>
const int N = 1000005;
long long m, n, o, p, x, y, z;
long long plus[N], tree[N], mul[N];
void build(long long, long long, long long);
void plusdown(long long, long long, long long, long long, long long, long long);
void pushdown(long long, long long, long long);
long long muldown(long long, long long, long long, long long, long long, long long);
long long query(long long, long long, long long, long long, long long);
int main() {
    scanf("%lld %lld %lld", &n, &m, &p);
    build(1, 1, n);
    while (m--) {
        scanf("%lld", &o);
        if (o == 1) {
            scanf("%lld %lld %lld", &x, &y, &z);
            muldown(1, 1, n, x, y, z);
        } else if (o == 2) {
            scanf("%lld %lld %lld", &x, &y, &z);
            plusdown(1, 1, n, x, y, z);
        } else {
            scanf("%lld %lld", &x, &y);
            printf("%lld\n", query(1, 1, n, x, y) % p);
        }
    }
    return 0;
}
inline void build(long long v, long long l, long long r) {
    if (l == r) {
        scanf("%lld", &tree[v]);
        tree[v] %= p;
        mul[v] = 1;
        return;
    }
    long long mid = (l + r) >> 1;
    build(v << 1, l, mid);
    build(v << 1 | 1, mid + 1, r);
    tree[v] = (tree[v << 1] + tree[v << 1 | 1]) % p;
    mul[v] = 1;
}
inline void plusdown(long long v, long long sl, long long sr, long long ul, long long ur, long long x) {
    if (sl == ul && sr == ur) {
        tree[v] = (tree[v] + x * (ur - ul + 1)) % p;
        plus[v] = (plus[v] + x) % p;
    } else {
        pushdown(v, sl, sr);
        long long mid = (sl + sr) >> 1;
        tree[v] = (tree[v] + x * (ur - ul + 1)) % p;
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
    tree[v << 1] = (tree[v << 1] * mul[v] + (mid - l + 1) * plus[v]) % p;
    plus[v << 1] = (plus[v << 1] * mul[v] + plus[v]) % p;
    mul[v << 1] = mul[v << 1] * mul[v] % p;
    tree[v << 1 | 1] = (tree[v << 1 | 1] * mul[v] + (r - mid) * plus[v]) % p;
    plus[v << 1 | 1] = (plus[v << 1 | 1] * mul[v] + plus[v]) % p;
    mul[v << 1 | 1] = mul[v << 1 | 1] * mul[v] % p;
    plus[v] = 0;
    mul[v] = 1;
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
        return tmp % p;
    }
}
inline long long muldown(long long v, long long sl, long long sr, long long ul, long long ur, long long x) {
    int tmp = 0;
    if (sl == ul && sr == ur) {
        tmp = (tree[v] * (x - 1)) % p;
        tree[v] = (tree[v] * x) % p;
        plus[v] = (plus[v] * x) % p;
        mul[v] = (mul[v] * x) % p;
        return tmp;
    } else {
        pushdown(v, sl, sr);
        long long mid = (sl + sr) >> 1;
        if (ul <= mid) {
            tmp += muldown(v << 1, sl, mid, ul, std::min(mid, ur), x);
        }
        if (ur > mid) {
            tmp += muldown(v << 1 | 1, mid + 1, sr, std::max(mid + 1, ul), ur, x);
        }
        tree[v] = (tree[v] + tmp) % p;
        return tmp % p;
    }
}