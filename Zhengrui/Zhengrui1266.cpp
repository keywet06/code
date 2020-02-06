#include <bits/stdc++.h>
const int N = 400005;
int cnt, n, k, x, y, z;
int head[N], next[N], to[N], wst[N], fa[N];
long long ans;
long long val[N], big[N], big2[N];
int insert(int u, int v, int s) {
    ++cnt;
    next[cnt] = head[u];
    head[u] = cnt;
    to[cnt] = v;
    wst[cnt] = s;
}
int addedge(int u, int v, int s) {
    insert(u, v, s);
    insert(v, u, s);
}
void dfs(int u, int f) {
    fa[u] = f;
    big[u] = val[u];
    for (int v = head[u]; v; v = next[v]) {
        if (to[v] == fa[u]) {
            continue;
        }
        val[to[v]] = val[u] + wst[v];
        dfs(to[v], u);
        if (big[to[v]] > big[u]) {
            big2[u] = big[u];
            big[u] = big[to[v]];
        } else if (big[to[v]] > big2[u]) {
            big2[u] = big[to[v]];
        }
    }
    if (!big2[u]) {
        return;
    }
    ans = std::max(ans, big[u] + big2[u] - 2 * val[u]);
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> k;
    for (int i = 1; i < n; ++i) {
        std::cin >> x >> y >> z;
        addedge(x, y, z);
    }
    dfs(1, 1);
    std::cout << ans * k << std::endl;
    return 0;
}