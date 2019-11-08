#include <bits/stdc++.h>
const int M = 20005;
const int N = 1005;
int cnt, n, m, x, y;
int duo[N], head[N], is[N], p[N], lock[N];
int edgex[M], edgey[M], next[M], to[M];
void insert(int, int);
void addedge(int, int);
int change(int);
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d", &edgex[i], &edgey[i]);
        ++duo[edgex[i]];
        ++duo[edgey[i]];
    }
    for (int i = 1; i <= n; ++i) {
        if (duo[i] < (n - 1) / 2) {
            continue;
        }
        memset(p, 0, sizeof(p));
        memset(is, 0, sizeof(is));
        memset(lock, 0, sizeof(lock));
        memset(head, 0, sizeof(head));
        p[i] = -1;
        cnt = 0;
        x = 1;
        is[i] = 2;
        for (int j = 1; j <= m; ++j) {
            if (edgex[j] == i) {
                is[edgey[j]] = 1;
            } else if (edgey[j] == i) {
                is[edgex[j]] = 1;
            }
        }
        for (int j = 1; j <= m; ++j) {
            if (is[edgex[j]] + is[edgey[j]] == 1) {
                addedge(edgex[j], edgey[j]);
            }
        }
        for (int j = 1; j <= n; ++j) {
            if (is[j] || p[j]) {
                continue;
            }
            y = 0;
            for (int u = head[j]; u; u = next[u]) {
                if (change(to[u])) {
                    p[j] = to[u];
                    p[to[u]] = j;
                    y = 1;
                    break;
                }
            }
            if (!y) {
                x = 0;
                break;
            }
        }
        if (x) {
            printf("Yes\n");
            for (int i = 1; i <= n; ++i) {
                printf("%d ", p[i]);
            }
            printf("\n");
            return 0;
        }
    }
    printf("No\n");
    return 0;
}
inline void insert(int x, int y) {
    ++cnt;
    next[cnt] = head[x];
    head[x] = cnt;
    to[cnt] = y;
}
inline void addedge(int x, int y) {
    insert(x, y);
    insert(y, x);
}
inline int change(int v) {
    if (!p[v]) {
        return 1;
    }
    if (lock[v]) {
        return 0;
    }
    lock[v] = 1;
    for (int u = head[p[v]]; u; u = next[u]) {
        if (to[u] != v && change(to[u])) {
            p[to[u]] = p[v];
            p[p[v]] = to[u];
            p[v] = 0;
            return 1;
        }
    }
    return 0;
}