#include <bits/stdc++.h>
const int N = 3005;
const long long INF = 1ll << 60;
using pairs = std::pair<int, int>;
int n, m, k;
int vis[N];
long long ans;
long long dis[N], a[N];
std::vector<pairs> e[N];
inline void dijstra(long long x) {
    std::priority_queue<pairs, std::vector<pairs>, std::greater<pairs> > q;
    for (int i = 1; i <= n; ++i) dis[i] = INF, vis[i] = 0;
    q.push(std::make_pair(0, 1));
    dis[1] = 0;
    while (q.size()) {
        pairs t = q.top();
        q.pop();
        int u = t.second, l = e[u].size();
        for (int i = 0; i < l; ++i) {
            int v = e[u][i].second;
            long long w = e[u][i].first - x;
            if (w < 0) w = 0;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                if (!vis[v]) vis[v] = 1, q.push(std::make_pair(dis[v], v));
            }
        }
        vis[u] = 0;
    }
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m >> k;
    for (int i = 1, u, v; i <= m; ++i) {
        long long w;
        std::cin >> u >> v >> w;
        e[u].push_back(std::make_pair(w, v));
        e[v].push_back(std::make_pair(w, u));
        a[i] = w;
    }
    dijstra(0);
    ans = dis[n];
    for (int i = 1; i <= m; ++i) {
        dijstra(a[i]);
        long long x = dis[n] + 1ll * k * a[i];
        ans = std::min(x, ans);
    }
    std::cout << ans << std::endl;
    return 0;
}