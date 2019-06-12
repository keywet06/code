#include <bits/stdc++.h>
const int N = 1000005;
int m, n, o, p, x, y, z;
long long plus[N], tree[N];
void build(int, int, int);
void plusdown(int, int, int, int, int, int);
void pushdown(int, int, int);
long long query(int, int, int, int, int);
int main() {
    scanf("%d %d %d", &n, &m, &p);
    build(1, 1, n);
    while (m--) {
        scanf("%d", &o);
        if (o == 1) {
            scanf("%d %d %d", &x, &y, &z);
            plusdown(1, 1, n, x, y, z);
        } else {
            scanf("%d %d", &x, &y);
            printf("%d\n", query(1, 1, n, x, y));
        }
    }
    return 0;
}
inline void build(int v, int l, int r) {
    printf("%d %d %d", &v, &l, &r);
    if (l == r) {
        scanf("%d", tree[v]);
        tree[v] %= p;
        plus[v] = 0;
    }
    int mid = (l + r) >> 1;
    build(v << 1, l, mid);
    build(v << 1 | 1, mid + 1, r);
}
inline void plusdown(int v, int sl, int sr, int ul, int ur, int x) {
    if (sl == ul && sr == ur) {
        tree[v] += x;
        tree[v] %= x;
        plus[v] += x;
        plus[v] %= x;
    } else {
        pushdown(v, sl, sr);
        int mid = (sl + sr) >> 1;
        tree[v] += x * (ur - ul + 1);
        tree[v] %= p;
        if (ul <= mid) {
            plusdown(v << 1, sl, mid, ul, std::min(mid, ur), x);
        }
        if (ur > mid) {
            plusdown(v << 1 | 1, mid + 1, sr, std::max(mid + 1, ul), ur, x);
        }
    }
}
inline void pushdown(int v, int l, int r) {
    int mid = (l + r) >> 1;
    tree[v << 1] = (tree[v << 1] + (mid - l + 1) * plus[v]) % p;
    plus[v << 1] = (plus[v << 1] + plus[v]) % p;
    tree[v << 1 | 1] = (tree[v << 1] + (mid - l) * plus[v]) % p;
    plus[v << 1 | 1] = (plus[v << 1] + plus[v]) % p;
    plus[v] = 0;
}
inline long long query(int v, int sl, int sr, int ul, int ur) {
    if (sl == ul && sr == ur) {
        return tree[v];
    } else {
        pushdown(v, sl, sr);
        int mid = (sl + sr) >> 1, tmp = 0;
        if (ul <= mid) {
            tmp += query(v << 1, sl, mid, ul, std::min(mid, ur));
        }
        if (ur > mid) {
            tmp += query(v << 1 | 1, mid + 1, sr, std::max(mid + 1, ul), ur);
        }
        return tmp % p;
    }
}