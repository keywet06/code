#include <bits/stdc++.h>
const int N = 100005;
const int M = 1000005;
class edge {
    public:
        int u, v;
};
int bcc_cnt, cnt, m, n, x, y;
int next[M], to[M];
int dfn[N], low[N], head[N], vis[N], isbcc[N];
std::set<int> bcc[N];
std::stack<edge> ed;
void addedge(int, int);
void insert(int, int);
void dfsinit();
void dfs(int, int = -1);
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d", &x, &y);
        addedge(x, y);
    }
    dfsinit();
    dfs(1);
    for (int i = 1; i <= n; ++i) {
        if (isbcc[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
    printf("%d\n", bcc_cnt);
    for (int i = 1; i <= bcc_cnt; ++i) {
        for (std::set<int>::iterator it = bcc[i].begin(); it != bcc[i].end(); ++it) {
            printf("%d ", *it);
        }
        printf("\n");
    }
    return 0;
}
inline void addedge(int x, int y) {
    insert(x, y);
    insert(y, x);
}
inline void insert(int x, int y) {
    ++cnt;
    next[cnt] = head[x];
    head[x] = cnt;
    to[cnt] = y;
}
inline void dfsinit() {
    cnt = 0;
}
inline void dfs(int v, int fa) {
    dfn[v] = low[v] = ++cnt;
    vis[v] = 1;
    int child = 0;
    for (int u = head[v]; u; u = next[u]) {
        if (!vis[to[u]]) {
            ed.push((edge){v, to[u]});
            ++child;
            dfs(to[u], fa);
            low[u] = std::min(low[u], low[v]);
            if (low[to[u]] >= dfn[v]) {
                isbcc[to[u]] = 1;
                ++bcc_cnt;
                while (1) {
                    edge x = ed.top();
                    ed.pop();
                    bcc[bcc_cnt].insert(x.u);
                    bcc[bcc_cnt].insert(x.v);
                    if (x.u == v && x.v == to[u]) {
                        break;
                    }
                }
            }
        } else if (dfn[to[u]] < dfn[v] && v != fa) {
            ed.push((edge){v, to[u]});
            low[v] = std::min(low[v], dfn[to[u]]);
        }
    }
    if (fa == -1 && child == 1) {
        isbcc[v] = 0;
    }
}