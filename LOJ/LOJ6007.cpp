#include <bits/stdc++.h>

using int64 = long long;

const int64 INF = 100000000000000000;
const int N = 1005;
const int M = 100005;
const int E = M << 1;

int n, m, S, T, cnt = 1, x, y, z;
int head[N], cur[N], dis[N];
int next[E], to[E];

int64 ans, sum;
int64 flow[E];
int64 val[N][N];

inline void insert(int u, int v, int64 f) {
    next[++cnt] = head[u], head[u] = cnt;
    to[cnt] = v, flow[cnt] = f;
}

inline void addedge(int u, int v, int64 f) { insert(u, v, f), insert(v, u, 0); }
inline void adddge(int u, int v, int64 f) { insert(u, v, f), insert(v, u, f); }

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
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> m, S = n * m + 1, T = n * m * 2;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> x, sum += x;
            if ((i ^ j) & 1) {
                addedge(S, i * m + j + 1, x);
                if (i) addedge(i * m + j + 1, i * m - m + j + 1, INF);
                if (j) addedge(i * m + j + 1, i * m + j, INF);
            } else {
                addedge(i * m + j + 1, T, x);
                if (i) addedge(i * m - m + j + 1, i * m + j + 1, INF);
                if (j) addedge(i * m + j, i * m + j + 1, INF);
            }
        }
    }
    std::cout << sum - Dinic(S, T) << std::endl;
    return 0;
}