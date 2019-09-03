#include <bits/stdc++.h>
const int C = 20;
const int INF = 1e9;
const int N = 1000005;
struct node {
    int l, r;
};
int operator < (node, node);
int read();
node a[N];
int m, n, x, y, ans = INF;
int top[N], fa[N][C + 5];
int main() {
    m = read();
    n = read();
    for (int i = 1; i <= n; ++i) {
        a[i].l = read();
        a[i].r = read();
        if (a[i].l > a[i].r) {
            a[i].r += m;
        }
    }
    std::sort(a + 1, a + 1 + n);
    top[n + 1] = INF;
    for (int i = n; i >= 1; --i) {
        top[i] = std::min(top[i + 1], a[i].l);
    }
    for (int i = 1, j = 1; i <= n; ++i) {
        while (j < n && top[j + 1] - 1 <= a[i].r) {
            ++j;
        }
        if (j != i) {
            fa[i][0] = j;
        }
    }
    for (int i = n; i >= 1; --i) {
        for (int j = 1; j <= C; ++j) {
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
        }
    }
    for (int i = 1; i <= n; ++i) {
        int u = i, tmp = 1;
        for (int j = C; j >= 0; --j) {
            if (fa[u][j] && a[fa[u][j]].r < a[i].l + m) {
                u = fa[u][j];
                tmp += 1 << j;
            }
        }
        if (a[u].r < a[i].l + m - 1 && fa[u][0]) {
            u = fa[u][0];
            ++tmp;
        }
        if (a[u].r >= a[i].l + m - 1) {
            ans = std::min(ans, tmp);
        }
    }
    if (ans == INF) {
        puts("impossible");
    } else {
        printf("%d\n", ans);
    }
}
inline int operator<(node a, node b) { return a.r < b.r; }
inline int read() {
    int x = 0, ch = getchar();
    while (ch < '0' || ch > '9') {
        ch = getchar();
    }
    x = ch ^ '0';
    ch = getchar();
    while ('0' <= ch && ch <= '9') {
        (x *= 10) += ch ^ '0';
        ch = getchar();
    }
    return x;
}