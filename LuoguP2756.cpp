#include <bits/stdc++.h>
class edge {
   public:
    edge *next, *ano;
    int to, liu;
};
const int INF = 0x3f3f3f3f;
const int M = 1000005;
const int N = 205;
edge e[M];
edge* cnt = e;
edge* li[M];
edge* head[N];
int cnt_li, m, n, x, y;
int vis[N], dis[N];
void insertliu(int, int, int);
void addliu(int, int, int);
int SPFA();
int dfs(int, int);
int Dinic();
int main() {
    scanf("%d %d", &m, &n);
    scanf("%d %d", &x, &y);
    while (~x) {
        addliu(x, y, 1);
        li[++cnt_li] = cnt;
        scanf("%d %d", &x, &y);
    }
    for (int i = 1; i <= m; ++i) {
        addliu(m + n + 1, i, 1);
    }
    for (int i = m + 1; i <= m + n; ++i) {
        addliu(i, m + n + 2, 1);
    }
    x = Dinic();
    if (!x) {
        printf("No Solution!\n");
    } else {
        printf("%d\n", x);
    }
    for (int i = 1; i <= cnt_li; ++i) {
        if (li[i]->liu) {
            printf("%d %d\n", li[i]->to, li[i]->ano->to);
        }
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
    queue.push(m + n + 1);
    dis[m + n + 1] = 0;
    vis[m + n + 1] = 1;
    while (!queue.empty()) {
        int v = queue.front();
        queue.pop();
        for (edge* u = head[v]; u; u = u->next) {
            if (u->liu && dis[v] + 1 < dis[u->to]) {
                dis[u->to] = dis[v] + 1;
                if (u->to == m + n + 2) {
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
    if (v == m + n + 2) {
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
        ans += dfs(n + m + 1, INF);
    }
    return ans;
}
