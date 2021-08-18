#include <bits/stdc++.h>

#define Debug std::cerr << "Debug(" << __LINE__ << "): "
#define Deb std::cerr

using int64 = long long;

const int64 INF = 100000000000000000;
const int N = 5005;
const int M = 500005;
const int E = M << 1;

int n, m, S, T, cnt = 1, x, y, z, c, l, r;
int head[N], cur[N], dis[N], dir[N], use[N];
int next[E], to[E];

int64 ans;
int64 flow[E];

inline void insert(int u, int v, int f) {
    next[++cnt] = head[u], head[u] = cnt;
    to[cnt] = v, flow[cnt] = f;
}

inline void addedge(int u, int v, int f) { insert(u, v, f), insert(v, u, 0); }

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

inline bool solve(int n, bool o = false) {
    // Debug << "solve(" << n << ")" << std::endl;
    cnt = 1, memset(head, 0, sizeof(head)), S = 2 * n + 1, T = 2 * n + 2;
    for (int i = 1; i <= n; ++i) addedge(S, i, 1), addedge(n + i, T, 1);
    for (int i = 1; i * i <= n * 2; ++i) {
        for (int j = std::max(1, i * i - n); j * 2 < i * i; ++j) {
            addedge(j, n + i * i - j, 1);
            // addedge(i * i - j, n + j, 1);
        }
    }
    ans = n - Dinic(S, T);
    // Debug << "ans = " << ans << ";" << std::endl;
    if (o) {
        // Debug << "dir = {0";
        for (int i = 1; i <= n; ++i) {
            for (int e = head[i]; e; e = next[e]) {
                if (to[e] != S && !flow[e]) use[dir[i] = to[e] - n] = 1;
            }
            // Deb << ", " << dir[i];
        }
        // Deb << "};" << std::endl;
        for (int i = 1; i <= n; ++i) {
            if (use[i]) continue;
            x = 0;
            for (int u = i; u; u = dir[u]) {
                if (x) std::cout << ' ';
                x = 1, std::cout << u;
            }
            std::cout << std::endl;
        }
    }
    return ans <= c;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> c, l = 1, r = 1600;
    while (l < r) {
        int mid = l + r + 1 >> 1;
        solve(mid) ? (l = mid) : (r = mid - 1);
    }
    std::cout << l << std::endl;
    solve(l, true);
    return 0;
}