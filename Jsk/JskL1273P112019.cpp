#include <iostream>
using namespace std;
const int maxn = 110;
const int inf = 0x3f3f3f3f;
int a[maxn];
int minv[4 * maxn], lazy[4 * maxn];
void pushup(int id) {
    minv[id] = min(minv[id << 1], minv[id << 1 | 1]);
}
void pushdown(int id) {
    if (lazy[id]) {
        lazy[id << 1] += lazy[id];
        lazy[id << 1 | 1] += lazy[id];
        minv[id << 1] += lazy[id];
        minv[id << 1 | 1] += lazy[id];
        lazy[id] = 0;
    }
}
void build(int id, int l, int r) {
    if (l == r) {
        minv[id] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);
    pushup(id);
}
void update(int id, int l, int r, int x, int y, int v) {
    if (x <= l && r <= y) {
        lazy[id] += v;
        minv[id] += v;
        return;
    }
    pushdown(id);
    int mid = (l + r) >> 1;
    if (x <= mid) {
        update(id << 1, l, mid, x, y, v);
    }
    if (y > mid) {
        update(id << 1 | 1, mid + 1, r, x, y, v);
    }
    pushup(id);
}
int query(int id, int l, int r, int x, int y) {
    if (x <= l && r <= y) {
        return minv[id];
    }
    pushdown(id);
    int mid = (l + r) >> 1;
    int ans = inf;
    if (x <= mid) {
        ans = min(ans, query(id << 1, l, mid, x, y));
    }
    if (y > mid) {
        ans = min(ans, query(id << 1 | 1, mid + 1, r, x, y));
    }
    return ans;
}
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    build(1, 1, n);
    int q;
    cin >> q;
    while (q--) {
        int x, y, v;
        cin >> x >> y >> v;
        update(1, 1, n, x, y, v);
    }
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        cout << query(1, 1, n, x, y) << endl;
    }
    return 0;
}
