#include <bits/stdc++.h>
class edge {
   public:
    edge *next, *ano;
    int to, liu;
};
const int INF = 0x3f3f3f3f;
const int M = 1000005;
const int N = 1005;
edge e[M];
edge* cnt = e;
edge* li[M];
edge* head[N];
int S = 1000, T = 1001, m, n, x, y, sum;
int vis[N], dis[N];
void insertliu(int, int, int);
void addliu(int, int, int);
int SPFA();
int dfs(int, int);
int Dinic();
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &x);
        addliu(S, i, x);
        sum += x;
    }
    for (int j = 1; j <= m; ++j) {
        scanf("%d", &x);
        addliu(j + n, T, x);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = m; j; --j) {
            addliu(i, j + n, 1);
        }
    }
    if (Dinic() < sum) {
        printf("0\n");
        return 0;
    }
    printf("1\n");
    for (int i = 1; i <= n; ++i) {
        for (edge *u = head[i]; u; u = u->next) {
            if (!u->liu) {
                printf("%d ", u->to - n);
            }
        }
        printf("\n");
    }
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
