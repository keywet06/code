#include <bits/stdc++.h>
const int INF = 0x3f3f3f3f;
const int N = 105;
const int M = 1005;
class edge {
    public:
        edge *ano, *next;
        int to, cost, liu;
};
edge e[M];
edge *cnt = e;
edge *head[N], *last[N];
int S, T, sum, x, n;
int a[N], b[N], dis[N], vis[N];
void insertliuedge(int, int, int, int);
void insertliu(int, int, int, int);
void addedgeliu(int, int, int, int);
int SPFA();
int Dinic();
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        sum += a[i];
    }
    sum /= n;
    S = n + 1;
    T = n + 2;
    for (int i = 1; i <= n; ++i) {
        if (a[i] <= sum) {
            insertliu(S, i, sum - a[i], 0);
            b[i] = 1;
        } else {
            insertliu(i, T, a[i] - sum, 0);
            b[i] = 0;
        }
    }
    for (int i = 1; i <= n; ++i) {
        x = i + 1;
        if (x > n) {
            x -= n;
        }
        addedgeliu(i, x, INF, 1);
    }
    printf("%d\n", Dinic());
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
    return dis[T] != dis[0];
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