#include <bits/stdc++.h>
const int N = 1000005;
int n, m, p, q, l, r;
int fi[N], ans[N], vis[N];
int find(int);
void hebin(int, int);
int main() {
    scanf("%d %d %d %d", &n, &m, &p, &q);
    for (int i = 1; i <= n; ++i) {
        fi[i] = i;
    }
    for (int i = m; i; --i) {
        l = (i * p + q) % n + 1;
        r = (i * q + p) % n + 1;
        if (l > r) {
            std::swap(l, r);
        }
        for (int j = l; j <= r; ++j) {
            while (vis[j]) {
                j = find(j) + 1;
            }
            if (j <= r) {
                hebin(j, r);
                ans[j] = i;
                vis[j] = 1;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        printf("%d\n", ans[i]);
    }
    return 0;
}
inline int find(int x) {
    return fi[x] == x ? x : fi[x] = find(fi[x]);
}
inline void hebin(int x, int y) {
    x = find(x);
    y = find(y);
    if (x > y) {
        fi[y] = x;
    } else {
        fi[x] = y;
    }
}