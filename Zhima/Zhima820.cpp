#include <bits/stdc++.h>

#define fi first
#define se second
#define mkp std::make_pair

using int64 = long long;
using pair = std::pair<int64, int>;

const int N = 200005;
const int M = 2000005;

int S, n, k, m, x, y, z, cnt;
int head[N], use[N];
int next[M], to[M];

int64 dis[N];
int64 val[M];

pair c;

std::priority_queue<pair, std::vector<pair>, std::greater<pair> > q;

inline void insert(int u, int v, int64 w) {
    next[++cnt] = head[u], head[u] = cnt;
    to[cnt] = v, val[cnt] = w;
}

inline void addedge(int u, int v, int64 w) { insert(u, v, w), insert(v, u, w); }

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> m >> k >> S;
    for (int i = 1; i <= m; ++i) std::cin >> x >> y >> z, addedge(x, y, z * 2);
    for (int i = 1; i <= k; ++i) {
        std::cin >> z >> y;
        while (y--) std::cin >> x, addedge(x, n + i, z);
    }
    memset(dis, 63, sizeof(dis));
    dis[S] = 0, q.push(mkp(dis[S], S));
    for (int r = 1; r < n + k; ++r) {
        do {
            c = q.top(), q.pop();
        } while (use[c.se] || dis[c.se] != c.fi);
        use[c.se] = 1;
        for (int e = head[c.se]; e; e = next[e]) {
            if (c.fi + val[e] < dis[to[e]]) {
                dis[to[e]] = c.fi + val[e];
                q.push(mkp(dis[to[e]], to[e]));
            }
        }
    }
    for (int i = 1; i <= n; ++i) std::cout << dis[i] / 2 << ' ';
    std::cout << std::endl;
    return 0;
}