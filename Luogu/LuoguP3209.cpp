#include <bits/stdc++.h>
const int N = 2e3 + 1e1;

int x[N << 4], y[N << 4], vis[N << 4];
int id[N];
int fa[N << 5];
int T, n, m;

inline int findfa(int x) { return fa[x] == x ? x : fa[x] = findfa(fa[x]); }

inline void initfa() {
    for (int i = 1; i <= m << 1; i++) fa[i] = i;
}

inline bool cross(int x1, int x2, int y1, int y2) {
    if (x1 == x2 || y1 == y2 || x1 == y2 || x2 == y1) return 0;
    if (x1 < x2 && y1 < y2 && x2 < y1) return 1;
    if (x2 < x1 && y2 < y1 && x1 < y2) return 1;
    return 0;
}

inline bool check() {
    initfa();
    for (int i = 1; i <= m; i++) {
        if (vis[i]) continue;
        for (int j = 1; j <= m; j++) {
            if (vis[j]) continue;
            if (!cross(x[i], x[j], y[i], y[j])) continue;
            int fai = findfa(i), faj = findfa(j);
            if (fai == faj) return 0;
            fa[fai] = findfa(j + m), fa[faj] = findfa(i + m);
        }
    }
    return 1;
}

inline void init() {
    memset(x, 0, sizeof(x));
    memset(y, 0, sizeof(y));
    memset(vis, 0, sizeof(vis));
    n = m = 0;
}

inline int getint() {
    int ret = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    while ('0' <= ch && ch <= '9') ret = ret * 10 + (ch - '0'), ch = getchar();
    return ret;
}
int main() {
    T = getint();

    while (T--) {
        init();
        n = getint(), m = getint();
        for (int i = 1; i <= m; i++) x[i] = getint(), y[i] = getint();
        for (int i = 1; i <= n; i++) id[getint()] = i;
        if (m > 3 * n + 6) {
            puts("NO");
            continue;
        }
        for (int i = 1, a, b; i <= m; i++) {
            a = id[x[i]], b = id[y[i]];
            x[i] = min(a, b), y[i] = max(a, b);
        }
        for (int i = 1; i <= m; i++)
            if (y[i] == x[i] + 1 || (y[i] == n && x[i] == 0)) vis[i] = 1;
        if (check())
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}