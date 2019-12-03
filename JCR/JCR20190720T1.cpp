#include <bits/stdc++.h>
struct point {
    long long sum, plus;
    point *lson, *rson;
};
const long long M = 8000000;
const long long N = 200000;
long long m, n, x, y, z;
long long a[N];
point p[M];
point *cnt = p;
point *v[N];
point **root_cnt = v;
point *new_point();
void build(point*, long long, long long);
long long fun(long long, long long);
void updata(point*, long long, long long);
long long query(point*, long long, long long);
int main() {
    // freopen("A.in", "r", stdin);
    // freopen("A.out", "w", stdout);
    scanf("%lld %lld", &n, &m);
    for (long long i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
    }
    build(*root_cnt = new_point(), 1, n);
    for (long long i = 1; i <= m; ++i) {
        scanf("%lld", &x);
        if (x == 1) {
            scanf("%lld %lld %lld", &x, &y, &z);
            updata(*++root_cnt = &(*new_point() = **root_cnt), 1, n);
        } else if (x == 2) {
            scanf("%lld", &x);
            *++root_cnt = &(*new_point() = *v[x]);
        } else {
            scanf("%lld %lld", &x, &y);
            printf("%lld\n", query(*root_cnt, 1, n));
        }
    }
    return 0;
}
inline point *new_point() {
    return ++cnt;
}
inline void build(point *v, long long l, long long r) {
    if (l == r) {
        v->sum = a[l];
        return;
    }
    long long mid = (l + r) >> 1;
    build(v->lson = new_point(), l, mid);
    build(v->rson = new_point(), mid + 1, r);
    v->sum = v->lson->sum + v->rson->sum;
}
inline long long fun(long long l, long long r) {
    return std::min(r, y) - std::max(l, x) + 1;
}
inline void updata(point *v, long long l, long long r) {
    v->sum += z * fun(l, r);
    if (x <= l && r <= y) {
        v->plus += z;
        return;
    }
    long long mid = (l + r) >> 1;
    if (x <= mid) {
        updata(v->lson = &(*new_point() = *v->lson), l, mid);
    }
    if (y > mid) {
        updata(v->rson = &(*new_point() = *v->rson), mid + 1, r);
    }
}
inline long long query(point *v, long long l, long long r) {
    if (x <= l && r <= y) {
        return v->sum;
    }
    long long ans = 0, mid = (l + r) >> 1;
    if (x <= mid) {
        ans += query(v->lson, l, mid);
    }
    if (y > mid) {
        ans += query(v->rson, mid + 1, r);
    }
    return ans + fun(l, r) * v->plus;
}