#include <bits/stdc++.h>
const int N = 2000005;
int bcnt, cnt, n, m, x, y, z;
int next[N], head[N], to[N], val[N], dfn[N], low[N], vis[N], bval[N], xs[N], ys[N], zs[N];
std::set<int> set[N];
std::vector<int> vector(N);
namespace subtask2 {
    int pn;
    int starts[N], ends[N], values[N], d[N], f[N];
    long long ans;
    long long size[N];
    int find(int);
    int cmp(int, int);
    int Main() {
        for (int i = 1; i <= m; ++i) {
            d[i] = i;
        }
        for (int i = 1; i <= n; ++i) {
            size[i] = 1;
        }
        for (int i = 1; i <= pn; ++i) {
            f[i] = i;
        }
        std::sort(d + 1, d + m + 1, cmp);
        for (int i = 1; i <= m; ++i) {
            x = find(starts[d[i]]);
            y = find(ends[d[i]]);
            if (x != y) {
                ans += size[x] * size[y] * values[d[i]];
                size[x] += size[y];
                f[y] = x;
            }
        }
        printf("%lld\n", ans);
        return 0;
    }
    inline int find(int x) {
        return f[x] == x ? x : f[x] = find(f[x]);
    }
    inline int cmp(int x, int y) {
        return values[x] < values[y];
    }
}
long long read();
void insert(int, int, int);
void addedge(int, int, int);
void tarjan(int, int);
int main() {
    n = read();
    m = read();
    for (int i = 1; i <= m; ++i) {
        xs[i] = x = read();
        ys[i] = y = read();
        zs[i] = z = read();
        addedge(x, y, z);
    }
    cnt = 0;
    tarjan(1, 1);
    cnt = 0;
    for (int i = 1; i <= m; ++i) {
        if (std::set_intersection(set[xs[i]].begin(), set[xs[i]].end(), set[ys[i]].begin(), set[ys[i]].end(), vector.begin()) - vector.begin() == 0) {
            ++cnt;
            subtask2::starts[cnt] = xs[i];
            subtask2::ends[cnt] = ys[i];
            subtask2::values[cnt] = zs[i];
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (std::set<int>::iterator it = set[i].begin(); it != set[i].end(); ++it) {
            ++cnt;
            subtask2::starts[cnt] = i;
            subtask2::ends[cnt] = *it + n;
            subtask2::values[cnt] = bval[*it];
        }
    }
    m = cnt;
    subtask2::pn = n + bcnt;
    subtask2::Main();
    return 0;
}
inline long long read() {
    static long long ch, x;
    ch = getchar();
    x = 0;
    while (ch < '0' || ch > '9') {
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x;
}
inline void insert(int x, int y, int z) {
    ++cnt;
    next[cnt] = head[x];
    head[x] = cnt;
    to[cnt] = y;
    val[cnt] = z;
}
inline void addedge(int x, int y, int z) {
    insert(x, y, z);
    insert(y, x, z);
}
inline void tarjan(int v, int fa) {
    #if !defined(ONLINE_JUDGE) && defined(DEBUG)
    fprintf(stderr, "Debug: tarjan(Point Biconnected Component)(%d, %d);\n", v, fa);
    #endif
    static std::stack<std::pair<int, std::pair<int, int> > > stack;
    static std::pair<int, std::pair<int, int> > pair;
    low[v] = dfn[v] = ++cnt;
    vis[v] = 1;
    for (int u = head[v]; u; u = next[u]) {
        if (to[u] == fa) {
            continue;
        }
        stack.push(std::make_pair(val[u], std::make_pair(v, to[u])));
        if (!vis[to[u]]) {
            tarjan(to[u], v);
            low[v] = std::min(low[to[u]], low[v]);
            if (dfn[v] <= low[to[u]]) {
                ++bcnt;
                do {
                    pair = stack.top();
                    stack.pop();
                    set[pair.second.first].insert(bcnt);
                    set[pair.second.second].insert(bcnt);
                    bval[bcnt] = std::max(bval[bcnt], pair.first);
                } while (pair.second.first != v || pair.second.second != to[u]);
            }
        } else {
            low[v] = std::min(low[v], dfn[to[u]]);
        }
    }
}