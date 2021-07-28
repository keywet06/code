#include <bits/stdc++.h>

const int C = 20;
const int N = 300005;

int n, q, m, k, cnt, x, y, a, b, cut, u, v, rt, ans, c, d;
int dfn[N], min[N], blo[N], size[N], in[N], deep[N], pre[N], ins[N];
int fa[N][C];

std::vector<int> to1[N], to2[N], to3[N];

std::stack<int> sta;

inline void tarjan(int u) {
    dfn[u] = min[u] = ++cnt, sta.push(u), ins[u] = 1;
    for (int v : to1[u]) {
        if (!dfn[v]) {
            tarjan(v);
            min[u] = std::min(min[u], min[v]);
        } else if (ins[v]) {
            min[u] = std::min(min[u], dfn[v]);
        }
    }
    if (dfn[u] == min[u]) {
        ++cut;
        while (sta.size()) {
            ++size[cut], blo[sta.top()] = cut, ins[sta.top()] = 0;
            if (sta.top() == u) {
                sta.pop();
                break;
            }
            sta.pop();
        }
    }
}

inline int &update(int &u) { return u = blo[u]; }

inline void update(int &u, int &v, int x, int y) {
    if (x <= y) return;
    if (x >= u) u = std::min(u, y);
    if (y <= v) v = std::max(x, v);
}

inline void dfs(int u) {
    for (int i = 1; i < C; ++i) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int v : to3[u]) {
        deep[v] = deep[u] + 1, pre[v] = pre[u] + size[v];
        dfs(v);
    }
}

inline int isanc(int u, int v) {
    int c = deep[v] - deep[u];
    if (c < 0) return 0;
    for (int i = 0; i < C; ++i) {
        if (c & (1 << i)) v = fa[v][i];
    }
    return u == v;
}

inline int &mad(int &x, int y) { return x = std::max(x, y); }

int main() {
    // freopen("celebration.in", "r", stdin);
    // freopen("celebration.out", "w", stdout);
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> m >> q >> k;
    for (int i = 1; i <= m; ++i) {
        std::cin >> x >> y;
        to1[x].push_back(y);
    }
    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) tarjan(i);
    }
    for (int u = 1; u <= n; ++u) {
        for (int v : to1[u]) {
            if (blo[u] != blo[v]) to2[blo[u]].push_back(blo[v]), ++in[blo[v]];
        }
    }
    for (int u = 1; u <= cut; ++u) {
        std::cout << in[u] << ' ';
        if (!in[u]) sta.push(u);
    }
    std::cout << std::endl;
    rt = sta.top(), pre[rt] = size[rt];
    for (int i = 1; i <= cut; ++i) {
        u = sta.top(), sta.pop();
        for (int v : to2[u]) {
            if (!--in[v]) sta.push(v), fa[v][0] = u, to3[u].push_back(v);
        }
    }
    dfs(rt);
    for (int i = 1; i <= q; ++i) {
        std::cin >> u >> v, update(u), v = update(v);
        if (k >= 1) std::cin >> x >> y, update(x), update(y);
        if (k >= 2) std::cin >> a >> b, update(a), update(b);
        ans = 0;
        if (isanc(u, v)) mad(ans, pre[v] - pre[fa[u][0]]);
        if (k >= 1) {
            if (isanc(u, x) && isanc(y, v)) {
                if (isanc(u, v) && (isanc(x, v) || isanc(v, x))) {
                    mad(ans, std::max(pre[x], pre[v]) -
                                 std::min(pre[fa[u][0]], pre[fa[y][0]]));
                } else {
                    mad(ans, pre[x] - pre[fa[u][0]] + pre[v] - pre[fa[y][0]]);
                }
            }
        }
        if (k >= 2) {
            if (isanc(u, a) && isanc(b, v)) {
                if (isanc(u, v) && (isanc(a, v) || isanc(v, a))) {
                    mad(ans, std::max(pre[a], pre[v]) -
                                 std::min(pre[fa[u][0]], pre[fa[b][0]]));
                } else {
                    mad(ans, pre[a] - pre[fa[u][0]] + pre[v] - pre[fa[b][0]]);
                }
            }
        }
        std::cout << ans << std::endl;
    }
    return 0;
}