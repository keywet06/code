#include <bits/stdc++.h>
struct point {
    long long size;
    point *lson, *rson;
};
struct node {
    long long a, b;
};
const long long M = 30000000;
long long ans, n, x;
point p[M];
point *cnt = p;
void insert(point*, long long, long long, long long);
point *dfs();
node hebin(point*, point*, long long, long long);
int main() {
    // freopen("B.in", "r", stdin);
    // freopen("B.out", "w", stdout);
    scanf("%lld", &n);
    dfs();
    printf("%lld\n", ans);
    return 0;
}
inline void insert(point *v, long long l, long long r) {
    if (l == r) {
        v->size = 1;
    } else {
        long long mid = (l + r) >> 1;
        v->size = 1;
        if (x <= mid) {
            insert(v->lson = ++cnt, l, mid);
        } else {
            insert(v->rson = ++cnt, mid + 1, r);
        }
    }
}
inline node hebin(point *v1, point *v2, long long l, long long r) {
    if (l == r) {
        printf("l == r\n");
        ++v1->size;
        return (node){0, 0};
    }
    long long mid = (l + r) >> 1, lson1 = 0, rson1 = 0, lson2 = 0, rson2 = 0;
    node a = (node){0, 0}, b = (node){0, 0};
    if (v1->lson) {
        lson1 = v1->lson->size;
    }
    if (v2->lson) {
        lson2 = v2->lson->size;
    }
    if (v1->rson) {
        rson1 = v1->rson->size;
    }
    if (v2->rson) {
        rson2 = v2->rson->size;
    }
    if (v1->lson && v2->lson) {
        a = hebin(v1->lson, v2->lson, l, mid);
    }
    if (v1->rson && v2->rson) {
        b = hebin(v1->rson, v2->rson, mid + 1, r);
    }
    if (!v1->lson && v2->lson) {
        v1->lson = v2->lson;
    }
    if (!v1->rson && v2->rson) {
        v1->rson = v2->rson;
    }
    v1->size += v2->size;
    return (node){lson1 * rson2 + a.a + b.a, lson2 * rson1 + a.b + b.b};
}
inline point *dfs() {
    scanf("%lld", &x);
    point *tmp;
    if (x) {
        tmp = ++cnt;
        insert(tmp, 1, n);
        return tmp;
    }
    node s = hebin(tmp = dfs(), dfs(), 1, n);
    ans += std::min(s.a, s.b);
    return tmp;
}