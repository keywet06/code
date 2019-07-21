#include <bits/stdc++.h>
struct point {
    int size;
    point *lson, *rson;
};
const int M = 30000000;
int ans, n, x;
point p[M];
point *cnt = p;
void insert(point*, int, int, int);
point *dfs();
int hebin(point*, point*, int, int);
int main() {
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
    scanf("%d", &n);
    dfs();
    printf("%d\n", ans);
    return 0;
}
inline void insert(point *v, int l, int r) {
    printf("insert(%d, %d, %d)\n", v - p, l, r);
    if (l == r) {
        v->size = 1;
    } else {
        int mid = (l + r) >> 1;
        v->size = 1;
        if (x <= mid) {
            insert(v->lson = ++cnt, l, mid);
        } else {
            insert(v->rson = ++cnt, mid + 1, r);
        }
    }
}
inline void hebin(point *v1, point *v2, int l, int r) {
    printf("hebin(%d, %d, %d, %d)\n", v1 - p, v2 - p, l, r);
    if (l == r) {
        ++v1->size;
        return 0;
    }
    int mid = (l + r) >> 1, lson1 = 0, rson1 = 0, lson2 = 0, rson2 = 0, ans = 0;
    if (v1->lson) {
        lson1 = v1->lson->size;
    }
    if (v2->lson) {
        lson2 = v2->rson->size;
    }
    if (v1->rson) {
        rson1 = v1->lson->size;
    }
    if (v2->rson) {
        rson2 = v2->rson->size;
    }
    if (v1->lson && v2->lson) {
        hebin(v1->lson, v2->lson, l, mid);
    }
    if (v1->rson && v2->rson) {
        hebin(v1->rson, v2->rson, mid + 1, r);
    }
    v1->size += v2->size;
    ans += std::min(lson1 * rson2, rson1 * lson2);
}
inline point *dfs() {
    printf("dfs()\n");
    scanf("%d", &x);
    point *tmp;
    if (x) {
        tmp = ++cnt;
        insert(tmp, 1, n);
        return tmp;
    }
    return tmp;
}