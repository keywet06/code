#ifndef STD_BITS_STDCPP_H
#define STD_BITS_STDCPP_H
#include <bits/stdc++.h>
#endif
const int N = 100005;
struct node {
    int l, r;
};
node a[N];
int l, n, x, y, cnt, nl, nr, nc;
int cmp(node, node);
int main() {
    scanf("%d %d", &l, &n);
    while (n--) {
        scanf("%d %d", &x, &y);
        if (x <= y) {
            ++cnt;
            a[cnt].l = x;
            a[cnt].r = y;
            ++cnt;
            a[cnt].l = x + l;
            a[cnt].r = y + l;
        } else {
            ++cnt;
            a[cnt].l = x;
            a[cnt].r = y + l;
        }
    }
    std::sort(a + 1, a + cnt + 1, cmp);
    nl = a[1].l;
    nr = a[1].r;
    nc = 1;
    for (int i = 2; i <= cnt; ++i) {
        if (nr - nl + 1 >= l) {
            printf("%d\n", nc);
            return 0;
        }
    }
    return 0;
}
inline int cmp(node x, node y) {
    if (x.l != y.l) {
        return x.l < y.l;
    }
    return x.r < y.r;
}