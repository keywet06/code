#include <bits/stdc++.h>
const int INF = 0x3f3f3f3f;
const int N = 1005;
const int M = 100005;
class edge {
    public:
        edge *ano, *next;
        int to, cost, liu;
};
edge e[M];
edge *cnt = e;
edge *head[N], *last[N];
int S = 1000, T = 1001, sum, x, n, m;
int a[N][N], dis[N], vis[N], s[N], t[N];
void insertliuedge(int, int, int, int);
void insertliu(int, int, int, int);
void addedgeliu(int, int, int, int);
int SPFA();
int Dinic();
int main() {
    scanf("%d %d", &m, &n);
    for (int i = 1; i <= m; ++i) {
        scanf("%d", &s[i]);
        insertliu(S, i, s[i], 0);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &t[i]);
        insertliu(i + m, T, t[i], 0);
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            scanf("%d", &a[i][j]);
            insertliu(i, j + m, INF, a[i][j]);
        }
    }
    printf("%d\n", Dinic());
    memset(head, 0, sizeof(head));
    for (int i = 1; i <= m; ++i) {
        insertliu(S, i, s[i], 0);
    }
    for (int i = 1; i <= n; ++i) {
        insertliu(i + m, T, t[i], 0);
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            insertliu(i, j + m, INF, -a[i][j]);
        }
    }
    printf("%d\n", -Dinic());
    return 0;
}
inline void insertliuadge(int x, int y, int z, int w) {
    ++cnt;
    cnt->next = head[x];
    head[x] = cnt;
    cnt->to = y;
    cnt->liu = z;
    cnt->cost = w;
}
inline void insertliu(int x, int y, int z, int w) {
    insertliuadge(x, y, z, w);
    cnt->ano = cnt + 1;
    insertliuadge(y, x, 0, -w);
    cnt->ano = cnt - 1;
}
inline void addedgeliu(int x, int y, int z, int w) {
    insertliu(x, y, z, w);
    insertliu(y, x, z, w);
}
inline int SPFA() {
    memset(dis, 127, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    std::queue<int> queue;
    dis[S] = 0;
    vis[S] = 1;
    queue.push(S);
    while (!queue.empty()) {
        int v = queue.front();
        queue.pop();
        vis[v] = 0;
        for (edge *u = head[v]; u; u = u->next) {
            if (u->liu && dis[v] + u->cost < dis[u->to]) {
                dis[u->to] = dis[v] + u->cost;
                last[u->to] = u;
                if (!vis[u->to]) {
                    vis[u->to] = 1;
                    queue.push(u->to);
                }
            }
        }
    }
    return dis[T] != dis[999];
}
inline int Dinic() {
    int ans = 0, sum, t;
    while (SPFA()) {
        sum = INF;
        for (edge *u = last[T]; u; u = last[u->ano->to]) {
            sum = std::min(sum, u->liu);
        }
        ans += sum * dis[T];
        for (edge *u = last[T]; u; u = last[u->ano->to]) {
            u->ano->liu += sum;
            u->liu -= sum;
        }
    }
    return ans;
}