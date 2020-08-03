#include <bits/stdc++.h>
const int N = 100010;
int n, m;
int root[N], ans[N], fun[N];
std::vector<int> G[N];
struct edge {
    int to, next;
} e[N * 2];
int head[N], ecnt;
int tag[N * 32], ncnt, ls[N * 32], rs[N * 32], min[N * 32];
int fa[N], top[N], son[N], dfn[N], sz[N], ed[N], dfsn, ct[N], rk[N], dep[N];
std::vector<int> pool;
int st[16][N], lg[N];
void adde(int from, int to) {
    e[++ecnt] = (edge){to, head[from]}, head[from] = ecnt;
    e[++ecnt] = (edge){from, head[to]}, head[to] = ecnt;
}
void dfs(int u, int f) {
    fa[u] = f, sz[u] = 1, dep[u] = dep[f] + 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f) {
            dfs(e[i].to, u);
            sz[u] += sz[e[i].to];
            ct[u] += ct[e[i].to];
            if (sz[e[i].to] > sz[son[u]]) son[u] = e[i].to;
        }
}

void dfs1(int u, int t) {
    top[u] = t, dfn[u] = ++dfsn, rk[dfsn] = u;
    if (son[u]) dfs1(son[u], t);
    for (int i = head[u]; i; i = e[i].next) {
        if (e[i].to != fa[u] && e[i].to != son[u]) {
            dfs1(e[i].to, e[i].to);
        }
    }
    ed[u] = dfsn;
}
void pre() {
    for (int i = 1; i <= n; i++) st[0][i] = ct[rk[i]];
    for (int i = 1; i <= 15; i++) {
        for (int j = 1; j + (1 << i) - 1 <= n; j++) {
            st[i][j] = std::min(st[i - 1][j], st[i - 1][j + (1 << i - 1)]);
        }
    }
    for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
}
int get(int l, int r) {
    int len = lg[r - l + 1];
    return std::min(st[len][l], st[len][r - (1ll << len) + 1]);
}
int apply() {
    if (pool.size()) {
        int u = pool.back();
        pool.pop_back();
        return tag[u] = ls[u] = rs[u] = 0, u;
    }
    return ++ncnt;
}
void pushup(int root, int l, int r) {
    min[root] = 1e9;
    int mid = (l + r) >> 1;
    if (ls[root]) {
        min[root] = std::min(min[root], min[ls[root]] - tag[root]);
    } else {
        min[root] = std::min(min[root], get(l, mid) - tag[root]);
    }
    if (rs[root]) {
        min[root] = std::min(min[root], min[rs[root]] - tag[root]);
    } else {
        min[root] = std::min(min[root], get(mid + 1, r) - tag[root]);
    }
}
void update(int &root, int l, int r, int start, int end) {
    if (!root) root = apply(), min[root] = get(l, r);
    if (start <= l && r <= end) {
        tag[root] += 2;
        min[root] -= 2;
        return;
    }
    int mid = (l + r) >> 1;
    if (start <= mid) update(ls[root], l, mid, start, end);
    if (end > mid) update(rs[root], mid + 1, r, start, end);
    pushup(root, l, r);
}
void del(int root) {
    if (!root) return;
    pool.push_back(root), del(ls[root]), del(rs[root]);
}
int query(int root, int l, int r, int start, int end) {
    if (start > end) return 1e9;
    if (!root) return get(std::max(l, start), std::min(r, end));
    if (start <= l && r <= end) return min[root];
    int mid = (l + r) >> 1, res = 1e9;
    if (start <= mid) res = std::min(res, query(ls[root], l, mid, start, end));
    if (end > mid) res = std::min(res, query(rs[root], mid + 1, r, start, end));
    return res - tag[root];
}
void merge(int &x, int y, int l, int r) {
    if (!x || !y) return x |= y, void();
    tag[x] += tag[y];
    if (l == r) return min[x] -= tag[y], void();
    int mid = (l + r) >> 1;
    merge(ls[x], ls[y], l, mid), merge(rs[x], rs[y], mid + 1, r),
        pushup(x, l, r), pool.push_back(y);
}
void update(int &root, int x) {
    while (top[x]) update(root, 1, n, dfn[top[x]], dfn[x]), x = fa[top[x]];
}
void dfs2(int u, int f) {
    ans[u] = 1e9;
    for (int i = head[u]; i; i = e[i].next) {
        if (e[i].to != f) {
            int v = e[i].to;
            dfs2(v, u), merge(root[u], root[v], 1, n);
            ans[v] = std::min(ans[v], ct[u] - ct[v] + 2),
            ans[u] = std::min(ans[u], ct[u] - ct[v] + 2);
        }
    }
    for (auto v : G[u]) update(root[u], v);
    ans[u] = std::min(ans[u], 2 + ct[u] +
                                  std::min(query(root[u], 1, n, 1, dfn[u] - 1),
                                           query(root[u], 1, n, ed[u] + 1, n)));
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    int m;
    std::cin >> n >> m;
    for (int i = 1, a, b; i < n; i++) {
        std::cin >> a >> b;
        adde(a, b);
    }
    for (int i = 1, a, b; i <= m - n + 1; i++) {
        std::cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
        ct[a]++, ct[b]++;
    }
    dfs(1, 0);
    dfs1(1, 1);
    pre();
    for (int i = head[1]; i; i = e[i].next) {
        dfs2(e[i].to, 1);
        del(root[e[i].to]);
    }
    for (int u = 1; u <= n; u++) {
        for (int i = head[u]; i; i = e[i].next) {
            if (dep[e[i].to] > dep[u]) fun[(i + 1) / 2] = ans[e[i].to];
        }
    }
    for (int i = 1; i < n; i++) std::cout << fun[i] << " ";
    std::cout << std::endl;
    return 0;
}