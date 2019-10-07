#include <bits/stdc++.h>
const int N = 200005;
int n, k, m, ans, tp;
int x[N], y[N], z[N], w[N], f[N], s[N];
int cmp1(int, int);
int cmp2(int, int);
int find(int);
void merge(int, int);
int main() {
    scanf("%d %d %d", &n, &k, &m);
    for (int i = 1; i < m; ++i) {
        scanf("%d %d %d %d", &x[i], &y[i], &z[i], &w[i]);
        f[i] = s[i] = i;
    }
    std::sort(f + 1, f + m, cmp1);
    ans = 0;
    tp = n - 1 - k;
    for (int i = 1; k; ++i) {
        if (find(x[f[i]]) != find(y[f[i]])) {
            --k;
            ans = std::max(ans, z[f[i]]);
            z[f[i]] = -1;
            merge(x[f[i]], y[f[i]]);
        }
    }
    std::sort(f + 1, f + m, cmp2);
    k += tp;
    for (int i = 1; k; ++i) {
        if (~z[f[i]] && find(x[f[i]]) != find(y[f[i]])) {
            --k;
            ans = std::max(ans, w[f[i]]);
            merge(x[f[i]], y[f[i]]);
        }
    }
    printf("%d\n", ans);
    return 0;
}
inline int cmp1(int x, int y) {
    return z[x] < z[y];
}
inline int cmp2(int x, int y) {
    return w[x] < w[y];
}
inline int find(int x) {
    return s[x] == x ? x : s[x] = find(s[x]);
}
inline void merge(int x, int y) {
    s[find(x)] = find(y);
}