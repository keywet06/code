#include <bits/stdc++.h>
const int N = 100005;
int n, k, o;
int a[N], b[N], c[N], v[N], f[N], q[N], e[N];
int sum[N << 3];
inline int cmp(int x, int y) {
    return a[x] < a[y] ||
           a[x] == a[y] && (b[x] < b[y] || b[x] == b[y] && c[x] < c[y]);
}
inline int cmp2(int x, int y) {
    return b[x] < b[y] || b[x] == b[y] && c[x] < c[y];
}
inline void plus(int u, int l, int r, int x, int y) {
    sum[u] += y;
    if (l == r) return;
    int mid = l + r >> 1;
    if (x <= mid) {
        plus(u << 1, l, mid, x, y);
    } else {
        plus(u << 1 | 1, mid + 1, r, x, y);
    }
}
inline int get(int u, int l, int r, int x, int y) {
    if (x <= l && r <= y) return sum[u];
    int mid = l + r >> 1, s = 0;
    if (x <= mid) s += get(u << 1, l, mid, x, y);
    if (y > mid) s += get(u << 1 | 1, mid + 1, r, x, y);
    return s;
}
inline void cdq(int l, int r) {
    if (l + 1 == r) {
        f[q[l]] = v[q[l]] - 1;
        return;
    }
    int mid = l + r >> 1, j = l;
    cdq(l, mid);
    cdq(mid, r);
    std::sort(q + l, q + mid, cmp2);
    std::sort(q + mid, q + r, cmp2);
    for (int i = mid; i < r; ++i) {
        while (j < mid && b[q[j]] <= b[q[i]]) {
            plus(1, 1, k, c[q[j]], v[q[j]]);
            ++j;
        }
        f[q[i]] += get(1, 1, k, 1, c[q[i]]);
    }
    for (int i = l; i < j; ++i) plus(1, 1, k, c[q[i]], -v[q[i]]);
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i] >> b[i] >> c[i];
        f[i] = i;
    }
    std::sort(f, f + n, cmp);
    o = 0;
    for (int i = 0; i < n; ++i) {
        if (i && a[f[i]] == a[f[i - 1]] && b[f[i]] == b[f[i - 1]] &&
            c[f[i]] == c[f[i - 1]]) {
            ++v[q[o - 1]];
        } else {
            v[q[o++] = f[i]] = 1;
        }
    }
    memset(f, 0, sizeof(f));
    cdq(0, o);
    for (int i = 0; i < n; ++i) e[f[i]] += v[i];
    for (int i = 0; i < n; ++i) std::cout << e[i] << '\n';
    return 0;
}