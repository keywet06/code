#include "kw/Tu.hpp"
#include "kw/DisjointSet.hpp"
const int M = 1000005;
const int N = 5005;
const int Q = 10005;
int n, m, q, opt, cnt, ans;
int x[M], y[M];
int vis[N], fin[N];
int ro[Q], rx[Q], ry[Q];
kw::DisjointSet<N> ds;
kw::Tu<N, M, int> Tu;
char ReadARealChar();
void dfs(int);
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d", &x[i], &y[i]);
        Tu.addedge(x[i], y[i], 1);
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i) {
        opt = ReadARealChar();
        if (opt == 'A') {
            ro[i] = 1;
            scanf("%d %d", &rx[i], &ry[i]);
        } else if (opt == 'D') {
            ro[i] = 2;
            scanf("%d %d", &rx[i], &ry[i]);
            Tu.deledge(rx[i], ry[i]);
        } else {
            ro[i] = 3;
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (vis[i]) {
            continue;
        }
        for (kw::Tu<N, M, int>::iterator it = Tu.GetHead(i); it; it = it->next) {
            ds.merge(i, it->to);
            vis[it->to] = 1;
        }
    }
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; ++i) {
        if (!vis[ds.find(i)]) {
            vis[ds.find(i)] = ++cnt;
        }
        fin[i] = vis[ds.find(i)];
    }
    Tu.clear();
    for (int i = 1; i <= m; ++i) {
        if (!Tu.GetIt(fin[x[i]], fin[y[i]])) {
            Tu.addedge(fin[x[i]], fin[y[i]], 1);
        } else {
            ++Tu.GetIt(fin[x[i]], fin[y[i]])->data;
            ++Tu.GetIt(fin[y[i]], fin[x[i]])->data;
        }
    }
    for (int i = 1; i <= q; ++i) {
        if (ro[i] == 1) {
            if (!Tu.GetIt(fin[rx[i]], fin[ry[i]])) {
                Tu.addedge(fin[rx[i]], fin[ry[i]], 1);
            } else {
                ++Tu.GetIt(fin[rx[i]], fin[ry[i]])->data;
                ++Tu.GetIt(fin[ry[i]], fin[rx[i]])->data;
            }
        } else if (ro[i] == 2) {
            if (Tu.GetIt(fin[rx[i]], fin[ry[i]])->data <= 1) {
                Tu.deledge(fin[rx[i]], fin[ry[i]]);
            } else {
                --Tu.GetIt(fin[rx[i]], fin[ry[i]])->data;
                --Tu.GetIt(fin[ry[i]], fin[rx[i]])->data;
            }
        } else {
            for (int i = 1; i <= cnt; ++i) {
                vis[i] = 0;
            }
            ans = 0;
            for (int i = 1; i <= cnt; ++i) {
                if (vis[i]) {
                    continue;
                }
                ++ans;
                dfs(i);
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}
inline char ReadARealChar() {
    char ch = getchar();
    while (ch == '\n' || ch == '\r' || ch == ' ') {
        ch = getchar();
    }
    return ch;
}
inline void dfs(int v) {
    vis[v] = 1;
    for (kw::Tu<N, M, int>::iterator it = Tu.GetHead(v); it; it = it->next) {
        if (!vis[it->to]) {
            dfs(it->to);
        }
    }
}