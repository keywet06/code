#include <bits/stdc++.h>
const int N = 1000005;
struct node {
    int id;
    long long len;
};
int n, cnt = 1, x, y, pu, pv, pe, s, l, r;
int head[N], to[N], next[N], val[N], vis[N], fa[N], fv[N];
long long aans, ans, tmp, sum, sr;
long long dep[N], dep2[N];
node que[N << 1];
std::vector<int> ring, edge;
inline node mn(int id, long long len) {
    node tmp;
    tmp.id = id, tmp.len = len;
    return tmp;
}
inline void insert(int u, int v, int value) {
    next[++cnt] = head[u];
    head[u] = cnt;
    to[cnt] = v;
    val[cnt] = value;
}
inline void addedge(int u, int v, int value) {
    insert(u, v, value);
    insert(v, u, value);
}
inline void dfs1(int u, int f, int fe) {
    std::cout << "dfs1(" << u << ", " << f << ", " << fe << ");" << std::endl;
    vis[u] = 1;
    fa[u] = f;
    fv[u] = val[fe];
    for (int e = head[u]; e; e = next[e]) {
        if (e == (fe ^ 1)) continue;
        if (vis[to[e]]) {
            pu = u;
            pv = to[e];
            pe = e;
            continue;
        }
        dfs1(to[e], u, e);
    }
}
inline void dfs2(int u, int f, int fe) {
    long long max = 0, max2 = 0;
    vis[u] = 2;
    dep2[u] = dep[u] = dep[f] + val[fe];
    for (int e = head[u]; e; e = next[e]) {
        if (vis[to[e]] == 2) continue;
        dfs2(to[e], u, e);
        dep2[u] = std::max(dep2[u], dep2[to[e]]);
        tmp = dep2[u] - dep[u];
        if (tmp > max2) max2 = tmp;
        if (max < max2) std::swap(max, max2);
    }
    std::cout << "d2: " << u << " " << f << " " << ans << " " << max + max2 << std::endl;
    ans = std::max(ans, max + max2);
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> x >> y;
        addedge(i, x, y);
    }
    for (int i = 1; i <= n; ++i) {
        if (vis[i]) continue;
        std::cout << i << std::endl;
        dfs1(i, 0, 0);
        std::cout << "dfs finished." << std::endl;
        std::cout << "pu = " << pu << "; pv = " << pv << ";" << std::endl;
        ring.clear(), edge.clear();
        for (int u = pv; u != pu; u = fa[u]) {
            ring.push_back(u);
            edge.push_back(fv[u]);
        }
        ring.push_back(pu), edge.push_back(val[pe]);
        int n = ring.size();
        for (int i = 0; i < n; ++i) vis[ring[i]] = 2;
        sum = ans = 0;
        for (int i = 0; i < n; ++i) dfs2(ring[i], 0, 0);
        std::cout << "dfs2 finished." << std::endl;
        for (int i = 0; i < n; ++i) std::cout << ring[i] << " ";
        std::cout << std::endl;
        for (int i = 0; i < n; ++i) std::cout << edge[i] << " ";
        std::cout << std::endl;
        for (int i = 0; i < n; ++i) std::cout << dep2[ring[i]] << " ";
        std::cout << std::endl;
        l = 1, r = 0;
        for (int i = 0; i < n; ++i) {
            tmp = sum - dep2[ring[i]];
            while (l <= r && que[r].len >= tmp) --r;
            que[++r] = mn(i, tmp);
            sum += edge[i];
        }
        sr = sum;
        for (int i = 0; i < n; ++i) {
            while (l <= r && que[l].id <= i) ++l;
            std::cout << "I: " << l << " " << r << " " << sum - que[l].len + dep2[ring[i]] << " " << ans << std::endl;
            if (l <= r) ans = std::max(ans, sum - que[l].len + dep2[ring[i]]);
            tmp = sum - dep2[ring[i]];
            while (l <= r && que[r].len >= tmp) --r;
            que[++r] = mn(i + n, tmp);
            std::cout << "J: " << l << " " << r << " " << que[r].len << std::endl;
            sum += edge[i];
        }
        std::cout << ans << std::endl;
        aans += ans;
    }
    std::cout << aans << std::endl;
    return 0;
}
