#include <bits/stdc++.h>
const int N = 2000005;
int acnt, bcnt, cnt, stat, n, m, x, y, z;
int next[N], head[N], to[N], val[N], dfn[N], low[N], vis[N],
    staa[N], stab[N], stac[N];
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
            ans += size[x] * size[y] * values[d[i]];
            size[x] += size[y];
            f[y] = x;
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
    while (m--) {
        x = read();
        y = read();
        z = read();
        addedge(x, y, z);
    }
    m = cnt = 0;
    tarjan(1, 1);
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
    low[v] = dfn[v] = ++cnt;
    vis[v] = 1;
    for (int u = head[v]; u; u = next[u]) {
        if (to[u] == fa) {
            continue;
        }
        if (!vis[to[u]]) {
            int tmp = ++stat;
            staa[stat] = val[u];
            stab[stat] = v;
            stac[stat] = to[u];
            tarjan(to[u], v);
            low[v] = std::min(low[to[u]], low[v]);
            if (dfn[v] < low[to[u]]) {
                ++m;
                subtask2::starts[m] = to[u];
                subtask2::ends[m] = v;
                subtask2::values[m] = val[u];
                --stat;
            } else if (dfn[v] == low[to[u]]) {
                ++bcnt;
                int max = 0;
                for (int i = tmp; i <= stat; ++i) {
                    max = std::max(max, staa[i]);
                }
                ++m;
                subtask2::starts[m] = bcnt + n;
                subtask2::ends[m] = v;
                subtask2::values[m] = max;
                for (int i = tmp; i <= stat; ++i) {
                    ++m;
                    subtask2::starts[m] = bcnt + n;
                    subtask2::ends[m] = stac[i];
                    subtask2::values[m] = max;
                }
                stat = tmp - 1;
            }
        } else {
            low[v] = std::min(low[v], dfn[to[u]]);
        }
    }
}