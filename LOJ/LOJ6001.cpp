#include <bits/stdc++.h>

using int64 = long long;

const int64 INF = 100000000000000000;

const int N = 205;
const int M = 5005;
const int E = M << 1;

char ch;

int n, m, S, T, cnt = 1, x, y, z;
int head[N], cur[N], dis[N];
int next[E], to[E];

int64 ans;
int64 flow[E];

inline void insert(int u, int v, int64 f) {
    next[++cnt] = head[u], head[u] = cnt;
    to[cnt] = v, flow[cnt] = f;
}

inline void addedge(int u, int v, int64 f) { insert(u, v, f), insert(v, u, 0); }

inline bool SPFA(int S, int T) {
    std::queue<int> q;
    memset(dis, 0, sizeof(dis));
    dis[S] = 1, q.push(S);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == T) break;
        for (int e = head[u]; e; e = next[e]) {
            if (flow[e] && !dis[to[e]]) dis[to[e]] = dis[u] + 1, q.push(to[e]);
        }
    }
    return bool(dis[T]);
}

inline int64 dfs(int u, int64 mf) {
    int64 f, ret = 0;
    if (u == T) return mf;
    for (int &e = cur[u]; e; e = next[e]) {
        if (!flow[e] || dis[u] + 1 != dis[to[e]]) continue;
        f = dfs(to[e], std::min(mf, flow[e]));
        flow[e] -= f, flow[e ^ 1] += f, ret += f, mf -= f;
        if (!mf) return ret;
    }
    return ret;
}

inline int64 Dinic(int S, int T) {
    int64 ret = 0;
    while (SPFA(S, T)) memcpy(cur, head, sizeof(head)), ret += dfs(S, INF);
    return ret;
}

int main() {
    scanf("%d %d", &m, &n), S = n + m + 1, T = n + m + 2;
    for (int i = 1; i <= m; ++i) {
        scanf("%d", &x), ans += x, addedge(n + i, T, x), ch = ' ';
        while (ch == ' ') scanf("%d%c", &x, &ch), addedge(x, n + i, INF);
    }
    for (int i = 1; i <= n; ++i) std::cin >> x, addedge(S, i, x);
    ans -= Dinic(S, T), x = 0;
    for (int i = 1; i <= m; ++i) {
        if (!dis[n + i]) {
            if (x) std::cout << ' ';
            x = 1, std::cout << i;
        }
    }
    std::cout << std::endl, x = 0;
    for (int i = 1; i <= n; ++i) {
        if (!dis[i]) {
            if (x) std::cout << ' ';
            x = 1, std::cout << i;
        }
    }
    std::cout << std::endl;
    std::cout << ans << std::endl;
    return 0;
}