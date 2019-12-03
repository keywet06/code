#include <bits/stdc++.h>
const int N = 100005;
const int M = 200005;
const int K = 55;
namespace kw {
    #include <bits/stdc++.h>
    const int INF = 0x7f7f7f7f;
    template<int n = N, int m = M> class Tu {
        public:
            class edge {
                public:
                    edge *next;
                    int to, cost;
            };
        private:
            edge ed[m];
            edge *cnt;
        public:
            edge *head[n];
            Tu();
            void insert(int, int, int);
            void addedge(int, int, int);
            int SPFA(int, int);
            int SPFA(int, int, int*);
            void clear();
    };
    template<int n, int m> inline Tu<n, m>::Tu() {
        memset(head, 0, sizeof(head));
        memset(ed, 0, sizeof(ed));
        cnt = ed;
    }
    template<int n, int m> inline void Tu<n, m>::insert(int x, int y, int z) {
        ++cnt;
        cnt->next = head[x];
        head[x] = cnt;
        cnt->to = y;
        cnt->cost = z;
    }
    template<int n, int m> inline void Tu<n, m>::addedge(int x, int y, int z) {
        insert(x, y, z);
        insert(y, x, z);
    }
    template<int n, int m> inline int Tu<n, m>::SPFA(int S, int T) {
        int dis[n], vis[n];
        std::queue<int> queue;
        memset(dis, 127, sizeof(dis));
        memset(vis, 0, sizeof(vis));
        queue.push(S);
        dis[S] = 0;
        vis[S] = 1;
        while (!queue.empty()) {
            int v = queue.front();
            queue.pop();
            vis[v] = 0;
            for (edge *u = head[v]; u; u = u->next) {
                if (dis[v] + u->cost < dis[u->to]) {
                    dis[u->to] = dis[v] + u->cost;
                    if (!vis[u->to]) {
                        queue.push(u->to);
                        vis[u->to] = 1;
                    }
                }
            }
        }
        if (dis[T] == INF) {
            return -1;
        } else {
            return dis[T];
        }
    }
    template<int n, int m> inline int Tu<n, m>::SPFA(int S, int T, int *dis) {
        int vis[n];
        std::queue<int> queue;
        for (int i = 0; i < n; ++i) {
            dis[i] = INF;
        }
        memset(dis, 127, sizeof(dis));
        memset(vis, 0, sizeof(vis));
        queue.push(S);
        dis[S] = 0;
        vis[S] = 1;
        while (!queue.empty()) {
            int v = queue.front();
            queue.pop();
            vis[v] = 0;
            for (edge *u = head[v]; u; u = u->next) {
                if (dis[v] + u->cost < dis[u->to]) {
                    dis[u->to] = dis[v] + u->cost;
                    if (!vis[u->to]) {
                        queue.push(u->to);
                        vis[u->to] = 1;
                    }
                }
            }
        }
        if (dis[T] == INF) {
            return -1;
        } else {
            return dis[T];
        }
    }
    template<int n, int m> inline void Tu<n, m>::clear() {
        cnt = ed;
        memset(head, 0, sizeof(head));
    }
};
int T, ans, m, n, k, p, x, y, z, cntl;
int dis[N], vis[N];
int dp[N][K], dped[N][K];
kw::Tu<> t, SPFAt;
int df(int);
int dfs(int, int);
void Main();
int main() {
    scanf("%d", &T);
    while (T--) {
        Main();
    }
    return 0;
}
void Main() {
    scanf("%d %d %d %d", &n, &m, &k, &p);
    SPFAt.clear();
    t.clear();
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d %d", &x, &y, &z);
        SPFAt.insert(x, y, z);
        t.insert(y, x, z);
    }
    SPFAt.SPFA(1, n, dis);
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            ++cntl;
            if (df(i)) {
                printf("-1\n");
                return;
            }
        }
    }
    ans = 0;
    memset(dp, 0, sizeof(dp));
    memset(dped, 0, sizeof(dped));
    for (int i = 0; i <= k; ++i) {
        ans += dfs(n, i);
        ans %= p;
    }
    printf("%d\n", ans);
    return;
}
inline int df(int x) {
    if (vis[x] && vis[x] < cntl) {
        return 0;
    }
    if (vis[x] == cntl) {
        return 1;
    }
    vis[x] = cntl;
    for (kw::Tu<>::edge *u = t.head[x]; u; u = u->next) {
        if (u->cost == 0 && df(u->to)) {
            return 1;
        }
    }
    return 0;
}
inline int dfs(int x, int y) {
    if (x == 1 && y == 0) {
        return 1;
    }
    if (dped[x][y]) {
        return dp[x][y];
    }
    dped[x][y] = 1;
    for (kw::Tu<>::edge *u = t.head[x]; u; u = u->next) {
        if (y - u->cost + dis[x] - dis[u->to] >= 0) {
            dp[x][y] += dfs(u->to, y - u->cost + dis[x] - dis[u->to]);
            dp[x][y] %= p;
        }
    }
    return dp[x][y];
}