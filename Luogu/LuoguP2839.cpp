#include <bits/stdc++.h>

const int N = 20010;
const int M = 1000010;
const int inf = 1 << 29;

inline char nc() {
    static char buf[100000], *p1 = buf, *p2 = buf;
    return p1 == p2 &&
                   (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2)
               ? EOF
               : *p1++;
}

inline void read(int &x) {
    int s = 0, w = 1;
    char c = nc();
    while (!isdigit(c)) {
        if (c == '-') w = -1;
        c = nc();
    }
    while (isdigit(c)) {
        s = (s << 3) + (s << 1) + c - '0';
        c = nc();
    }
    x = s * w;
}

inline void write(int x) {
    if (x < 0) x = -x, putchar('-');
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
struct node {
    int lmax, rmax, ls, rs, sum;
} t[M];

int cnt, rt[N];

inline void push_up(int h) {
    t[h].sum = t[t[h].ls].sum + t[t[h].rs].sum;
    t[h].lmax = std::max(t[t[h].ls].lmax, t[t[h].rs].lmax + t[t[h].ls].sum);
    t[h].rmax = std::max(t[t[h].rs].rmax, t[t[h].ls].rmax + t[t[h].rs].sum);
}
int build(int l, int r) {
    int h = ++cnt;
    if (l == r) {
        t[h].lmax = t[h].rmax = t[h].sum = 1;
        return h;
    }
    int mid = (l + r) >> 1;
    t[h].ls = build(l, mid);
    t[h].rs = build(mid + 1, r);
    push_up(h);
    return h;
}
void ins(int &h, int lastroot, int l, int r, int x, int y) {
    h = ++cnt;
    t[h] = t[lastroot];
    if (l == r) {
        t[h].lmax = t[h].rmax = t[h].sum = y;
        return;
    }
    int mid = (l + r) >> 1;
    if (x <= mid)
        t[h].rs = t[lastroot].rs, ins(t[h].ls, t[lastroot].ls, l, mid, x, y);
    else
        t[h].ls = t[lastroot].ls,
        ins(t[h].rs, t[lastroot].rs, mid + 1, r, x, y);
    push_up(h);
}
int qus(int h, int l, int r, int x, int y) {
    if (l >= x && r <= y) return t[h].sum;
    int mid = (l + r) >> 1;
    return y <= mid ? qus(t[h].ls, l, mid, x, y)
                    : (x >= mid + 1 ? qus(t[h].rs, mid + 1, r, x, y)
                                    : qus(t[h].ls, l, mid, x, mid) +
                                          qus(t[h].rs, mid + 1, r, mid + 1, y));
}
int qlm(int h, int l, int r, int x, int y) {
    if (l >= x && r <= y) return t[h].lmax;
    int mid = (l + r) >> 1;
    if (y <= mid)
        return qlm(t[h].ls, l, mid, x, y);
    else if (x >= mid + 1)
        return qlm(t[h].rs, mid + 1, r, x, y);
    else
        return std::max(qlm(t[h].ls, l, mid, x, mid),
                        qus(t[h].ls, l, mid, x, mid) +
                            qlm(t[h].rs, mid + 1, r, mid + 1, y));
}
int qur(int h, int l, int r, int x, int y) {
    if (l >= x && r <= y) return t[h].rmax;
    int mid = (l + r) >> 1;
    return y <= mid
               ? qur(t[h].ls, l, mid, x, y)
               : (x >= mid + 1 ? qur(t[h].rs, mid + 1, r, x, y)
                               : std::max(qur(t[h].rs, mid + 1, r, mid + 1, y),
                                          qus(t[h].rs, mid + 1, r, mid + 1, y) +
                                              qur(t[h].ls, l, mid, x, mid)));
}
int n, Q;
int q[4];
inline bool check(int k, int a, int b, int c, int d) {
    int sum = 0;
    if (c - 1 >= b + 1) sum += qus(rt[k], 1, n, b + 1, c - 1);
    sum += qur(rt[k], 1, n, a, b);
    sum += qlm(rt[k], 1, n, c, d);
    return sum >= 0;
}
struct node2 {
    int pos, x;
} a[N];
inline bool cmp(const node2 &a, const node2 &b) { return a.x < b.x; }
int pre;
int main() {
    read(n);
    for (int i = 1; i <= n; i++) read(a[i].x), a[i].pos = i;
    std::sort(a + 1, a + n + 1, cmp);
    rt[1] = build(1, n);
    for (int i = 2; i <= n + 1; i++) {
        ins(rt[i], rt[i - 1], 1, n, a[i - 1].pos, -1);
    }
    read(Q);
    while (Q--) {
        read(q[0]), read(q[1]), read(q[2]), read(q[3]);
        for (int i = 0; i < 4; i++) q[i] = (q[i] + pre) % n;
        std::sort(q, q + 4);
        int l = 1, r = n, ans;
        while (l <= r) {
            int mid = (l + r) >> 1;
            check(mid, q[0] + 1, q[1] + 1, q[2] + 1, q[3] + 1)
                ? (l = mid + 1, ans = mid)
                : r = mid - 1;
        }
        write(a[ans].x), putchar(10), pre = a[ans].x;
    }
}