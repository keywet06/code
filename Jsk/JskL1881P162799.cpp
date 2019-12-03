#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int N = 10000 + 5;
const int B = pow(N, 2.0 / 3);
struct Q {
    int l, r, t, id;
    bool operator < (const Q &b) const {
        if (l / B == b.l / B) {
            if (r / B == b.r / B) return t < b.t;
            else return r / B < b.r / B;
        } else return l / B < b.l / B;
    }
}q[N];
struct M {
    int p, x, y;
} md[N];
int a[N], n, m, k, tim, tans, ans[N], cnt[N], b[N];
int l = 1, r = 0, t = 0;
void update(int x, int f) {
    cnt[x] += f;
    if (cnt[x] == 0 && f == -1) tans--;
    if (cnt[x] == 1 && f == 1) tans++;
}
void updateTime(int t, int f) {
    if (f == 1) {
        if (l <= md[t].p && md[t].p <= r) update(md[t].x, -1), update(md[t].y, 1);
        a[md[t].p] = md[t].y;
    } else {
        if (l <= md[t].p && md[t].p <= r) update(md[t].y, -1), update(md[t].x, 1);
		a[md[t].p] = md[t].x;
    }
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    for (int i = 1; i <= m; i++) {
        int op, l, r;
        scanf("%d%d%d", &op, &l, &r);
        if (op == 1) q[++k] = {l, r, tim, k};
        else {
            md[++tim] = {l, b[l], r};
            b[l] = r;
        }
    }
    sort(q + 1, q + k + 1);
    for (int i = 1; i <= k; i++) {
        while (t < q[i].t) updateTime(++t, 1);
        while (t > q[i].t) updateTime(t--, -1);
        while (l < q[i].l) update(a[l++], -1);
        while (l > q[i].l) update(a[--l], 1);
        while (r < q[i].r) update(a[++r], 1);
        while (r > q[i].r) update(a[r--], -1);
        ans[q[i].id] = tans;
    }
    for (int i = 1; i <= k; i++) printf("%d\n", ans[i]);
    return 0;
}
