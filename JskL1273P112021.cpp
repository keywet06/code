#include <iostream>
using namespace std;
const int maxn = 100010;
int c[maxn];
struct node {
    int maxlenl[2], maxlenr[2], maxlen[2];
    int len, lazy;
    void reverse() {
        swap(maxlenl[0], maxlenl[1]);
        swap(maxlenr[0], maxlenr[1]);
        swap(maxlen[0], maxlen[1]);
    }
} T[4 * maxn];
void pushup(node &fa, node &lson, node &rson) {
    for (int i = 0; i < 2; ++i) {
        fa.maxlen[i] = max(lson.maxlen[i], rson.maxlen[i]);
        fa.maxlen[i] = max(fa.maxlen[i], lson.maxlenr[i] + rson.maxlenl[i]);
        fa.maxlenl[i] = lson.maxlenl[i];
        if (lson.maxlenl[i] == lson.len) {fa.maxlenl[i] += rson.maxlenl[i];}
        fa.maxlenr[i] = rson.maxlenr[i];
        if (rson.maxlenr[i] == rson.len) {fa.maxlenr[i] += lson.maxlenr[i];}
    }
    fa.len = lson.len + rson.len;
}
void pushdown(int id) {
    if (T[id].lazy) {
        T[id << 1].reverse();
        T[id << 1].lazy ^= 1;
        T[id << 1 | 1].reverse();
        T[id << 1 | 1].lazy ^= 1;
        T[id].lazy = 0;
    }
}
void build(int id, int l, int r) {
    if (l == r) {
        T[id].maxlen[c[l]] = T[id].maxlenl[c[l]] = T[id].maxlenr[c[l]] = 1;
        T[id].len = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);
    pushup(T[id], T[id << 1], T[id << 1 | 1]);
}
void update(int id, int l, int r, int x, int y) {
    if (x <= l && r <= y) {
    	T[id].reverse();
        T[id].lazy ^= 1;
        return;
    }
    pushdown(id);
    int mid = (l + r) >> 1;
    if (x <= mid) {update(id << 1, l, mid, x, y);}
    if (y > mid) {update(id << 1 | 1, mid + 1, r, x, y);}
    pushup(T[id], T[id << 1], T[id << 1 | 1]);
}
node query(int id, int l, int r, int x, int y) {
    if (x <= l && r <= y) {return T[id];}
    pushdown(id);
    int mid = (l + r) >> 1;
    node tmp[3];
    int t = 0;
    if (x <= mid) {
        tmp[1] = query(id << 1, l, mid, x, y);
        ++t;
    }
    if (y > mid) {
        tmp[2] = query(id << 1 | 1, mid + 1, r, x, y);
        t += 2;
    }
    if (t < 3) {return tmp[t];}
    else {
        pushup(tmp[0], tmp[1], tmp[2]);
        return tmp[0];
    }
    
}
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> c[i];
    }
    build(1, 1, n);
    int m;
    cin >> m;
    while (m--) {
        int d, x, y;
        cin >> d >> x >> y;
        if (d == 0) {
            node res = query(1, 1, n, x, y);
            cout << res.maxlen[1] << endl;
        } else {update(1, 1, n, x, y);}
    }
    return 0;
}
