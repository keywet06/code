#include <bits/stdc++.h>
const int N = 600005;
int n, k, x, y;
int max[N], b[N], p[N], d[N], s[N], t1[N], t2[N];
long long z;
inline int cmp(int x, int y) { return t1[x] < t1[y]; }
inline void pushup(int u) {
    max[u] =
        p[max[u << 1]] > p[max[u << 1 | 1]] ? max[u << 1] : max[u << 1 | 1];
}
inline void build(int u, int l, int r) {
    if (l == r) {
        max[u] = l;
        return;
    }
    int mid = l + r >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    pushup(u);
}
inline int query(int u, int l, int r, int x) {
    if (r <= x) {
        return max[u];
    }
    int mid = l + r >> 1, ans1, ans2;
    ans1 = query(u << 1, l, mid, x);
    ans2 = x > mid ? query(u << 1 | 1, mid + 1, r, x) : 0;
    return p[ans1] > p[ans2] ? ans1 : ans2;
}
inline void update(int u, int l, int r, int x) {
    if (l == r) {
        max[u] = 0;
        return;
    }
    int mid = l + r >> 1;
    if (x <= mid) {
        update(u << 1, l, mid, x);
    } else {
        update(u << 1 | 1, mid + 1, r, x);
    }
    pushup(u);
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        std::cin >> t1[i] >> t2[i];
        s[i] = i;
    }
    for (int i = 1; i <= k; ++i) {
        std::cin >> d[i];
    }
    std::sort(s + 1, s + n + 1, cmp);
    std::sort(d + 1, d + k + 1);
    for (int i = 1; i <= n; ++i) {
        b[i] = t1[s[i]];
        p[i] = t2[s[i]];
    }
    build(1, 1, n);
    b[n + 1] = d[k] + 1;
    for (int i = 1; i <= k; ++i) {
        x = std::upper_bound(b + 1, b + n + 2, d[i]) - b - 1;
        if (!x) continue;
        y = query(1, 1, n, x);
        if (!y) continue;
        update(1, 1, n, y);
        z += p[y];
    }
    std::cout << z << std::endl;
    return 0;
}