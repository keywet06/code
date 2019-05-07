#include <bits/stdc++.h>
const int int_INF = 1 << 30;
const int N = 1000005;
int S, T, ans, cnt, n, m;
int head[N], dis[N], next[N], to[N], liu[N];
void insert(int, int, int);
void insert2(int, int, int);
void Dinic(int &, int, int);
int SPFA();
int dfs(int, int);
int main() {
    scanf("%d %d", &n, &m);
    while (scanf("%d %d", &S, &T) && ~S && ~T) {
        insert(S, T, 1);
    }
    S = 0;
    T = n + 1;
    for (int i = 1; i <= m; ++i) {
        insert(S, i, 1);
    }
    for (int i = m + 1; i <= n; ++i) {
        insert(i, T, 1);
    }
    Dinic(ans, S, T);
    printf("%d\n", ans);
    return 0;
}
void insert(int x, int y, int z) {
    insert2(x, y, z);
    insert2(y, x, 0);
}
void insert2(int x, int y, int z) {
    ++cnt;
    next[cnt] = head[x];
    head[x] = cnt;
    to[cnt] = y;
    liu[cnt] = z;
}
void Dinic(int &res, int S, int T) {
    res = 0;
    while (SPFA()) {
        res += dfs(S, int_INF);
    }
}
int SPFA() {
    std::queue<int> q;
    memset(dis, -1, sizeof(dis));
    q.push(S);
    dis[S] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = head[u]; v; v = next[v]) {
            if (dis[to[v]] == -1 && liu[v] > 0) {
                q.push(to[v]);
                dis[to[v]] = dis[u] + 1;
            }
        }
    }
    return ~dis[T];
}
int dfs(int u, int r) {
    if (u == T) {
        return r;
    }
    int tmp, l = 0;
    for (int i = head[u]; i; i = next[i]) {
        if (dis[to[i]] == dis[u] + 1 && liu[i]) {
            tmp = dfs(to[i], std::min(r - l, liu[i]));
            liu[i] -= tmp;
            liu[i ^ 1] += tmp;
            l += tmp;
            if (l == r) {
                break;
            }
        }
    }
    if (!l) {
        dis[u] = -1;
    }
    return l;
}
