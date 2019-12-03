#include <bits/stdc++.h>
const int M = 200005;
const int N = 20005;
int cnt, l, r, m, mid, n, x, y, z;
int next[M], to[M], val[M];
int head[N], blwh[N];
void insert(int, int, int);
void addedge(int, int, int);
int check();
int dfs(int);
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d %d", &x, &y, &z);
        addedge(x, y, z);
    }
    l = 0;
    r = 1e9;
    while (l < r) {
        mid = (l + r + 1) >> 1;
        if (check()) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    printf("%d\n", l);
    return 0;
}
inline void insert(int x, int y, int z) {
    ++cnt;
    next[cnt] = head[x];
    head[x] = cnt;
    to[cnt] = y;
    val[cnt] = z;
}
inline void addedge(int x, int y, int z) {
    insert(x, y, z);
    insert(y, x, z);
}
inline int check() {
    memset(blwh, 0, sizeof(blwh));
    for (int i = 1; i <= n; ++i) {
        if (!blwh[i]) {
            blwh[i] = 1;
            if (dfs(i)) {
                return 1;
            }
        }
    }
    return 0;
}
inline int dfs(int v) {
    for (int u = head[v]; u; u = next[u]) {
        if (val[u] < mid || blwh[to[u]] == 3 - blwh[v]) {
            continue;
        }
        if (blwh[to[u]]) {
            return 1;
        }
        blwh[to[u]] = 3 - blwh[v];
        if (dfs(to[u])) {
            return 1;
        }
    }
    return 0;
}