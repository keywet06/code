#include <bits/stdc++.h>
class edge {
   public:
    edge *next, *ano;
    int to, liu;
};
const int INF = 0x3f3f3f3f;
const int M = 1000005;
const int N = 20005;
edge e[M];
edge* cnt = e;
edge* li[M];
edge* head[N];
int S = 20000, T = 20001, now, m, n, x, y, ans;
int vis[N], dis[N], las[N], isq[N];
void insertliu(int, int, int);
void addliu(int, int, int);
int SPFA();
int dfs(int, int);
int Dinic();
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        addliu(S, 2 * i - 1, 1);
        addliu(2 * i, T, 1);
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d", &x, &y);
        addliu(2 * x - 1, 2 * y, 1);
    }
    ans = Dinic();
    memset(vis, 0, sizeof(vis));
    for (int j = 1; j <= n; ++j) {
        if (!vis[j]) {
            now = j;
            while (1) {
                printf("%d ", now);
                vis[now] = 1;
                x = 1;
                for (edge *u = head[now * 2 - 1]; u; u = u->next) {
                    if (u->liu == 0 && u->to != S) {
                        now = (u->to + 1) / 2;
                        x = 0;
                        break;
                    }
                }
                if (x) {
                    break;
                }
            }
            printf("\n");
        }
    }
    printf("%d\n", n - ans);
    return 0;
}
inline void insertliu(int x, int y, int z) {
    ++cnt;
    cnt->next = head[x];
    head[x] = cnt;
    cnt->to = y;
    cnt->liu = z;
}
inline void addliu(int x, int y, int z) {
    insertliu(x, y, z);
    cnt->ano = cnt + 1;
    insertliu(y, x, 0);
    cnt->ano = cnt - 1;
}
inline int SPFA() {
    std::queue<int> queue;
    memset(dis, 127, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    queue.push(S);
    dis[S] = 0;
    vis[S] = 1;
    while (!queue.empty()) {
        int v = queue.front();
        queue.pop();
        for (edge* u = head[v]; u; u = u->next) {
            if (u->liu && dis[v] + 1 < dis[u->to]) {
                dis[u->to] = dis[v] + 1;
                las[u->to] = v;
                if (u->to == T) {
                    return 1;
                }
                if (!vis[u->to]) {
                    queue.push(u->to);
                    vis[u->to] = 1;
                }
            }
        }
    }
    return 0;
}
inline int dfs(int v, int res) {
    if (v == T) {
        return res;
    }
    int ans = 0, tmp;
    for (edge* u = head[v]; u; u = u->next) {
        if (u->liu && dis[u->to] == dis[v] + 1) {
            tmp = dfs(u->to, std::min(res, u->liu));
            u->liu -= tmp;
            u->ano->liu += tmp;
            ans += tmp;
            res -= tmp;
            if (!res) {
                break;
            }
        }
    }
    if (!ans) {
        dis[v] = 0;
    }
    return ans;
}
inline int Dinic() {
    int ans = 0;
    while (SPFA()) {
        ans += dfs(S, INF);
    }
    return ans;
}