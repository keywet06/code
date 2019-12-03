#include <bits/stdc++.h>
class node {
    public:
        long long to, next;
};
const long long N = 300005;
const long long M = 600005;
long long CLOCK, cnt, ans, m, n, q, x, y, z, innow, outnow;
long long head[N], val[N], dfn[N], undfn[N], deep[N], ava[N], lg[N];
long long fat[N][30];
node edge[M];
std::multiset<long long> now;
std::multiset<long long> in[N], out[N];
void insert(long long, long long);
void addedge(long long, long long);
void dfs(long long, long long);
void dfs2(long long, long long);
long long lca(long long, long long);
int main() {
    scanf("%lld %lld %lld", &n, &m, &q);
    for (long long i = 1; i < n; ++i) {
        scanf("%lld %lld", &x, &y);
        addedge(x, y);
    }
    dfs(1, 1);
    dfs2(1, 1);
    for(long long i = 1; i <= n; ++i) {
        lg[i] = lg[i - 1] + ((1 << lg[i - 1]) == i);
    }
    for (long long i = 1; i <= q; ++i) {
        scanf("%lld %lld %lld", &x, &y, &z);
        in[x].insert(dfn[z]);
        out[y + 1].insert(dfn[z]);
    }
    innow = 1;
    outnow = 1;
    ans = 0;
    for (long long i = 1; i <= n; ++i) {
        ans += val[i] - 1;
    }
    for (long long i = 1; i <= m; ++i) {
        for (std::multiset<long long>::iterator it = in[i].begin(); it != in[i].end(); ++it) {
            if (now.find(*it) == now.end()) {
                std::set<long long>::iterator its = now.upper_bound(*it);
	            x = lca(*its, *it);
                ans -= ava[undfn[*it]] - ava[undfn[x]];
            }
            now.insert(*it);
        }
        for (std::multiset<long long>::iterator it = out[i].begin(); it != out[i].end(); ++it) {
            now.erase(now.find(*it));
            if (now.find(*it) == now.end()) {
                std::set<long long>::iterator its = now.upper_bound(*it);
	            x = lca(*its, *it);
                ans += ava[undfn[*it]] - ava[undfn[x]];
            }
        }
        printf("%lld ", ans);
    }
    return 0;
}
inline void insert(long long x, long long y) {
    ++cnt;
    edge[cnt].next = head[x];
    head[x] = cnt;
    edge[cnt].to = y;
}
inline void addedge(long long x, long long y) {
    insert(x, y);
    insert(y, x);
}
inline void dfs(long long v, long long fa) {
    val[v] = 1;
    dfn[v] = ++CLOCK;
    deep[v] = deep[fa] + 1;
    undfn[CLOCK] = v;
    for (long long u = head[v]; u; u = edge[u].next) {
        if (edge[u].to == fa) {
            continue;
        }
        dfs(edge[u].to, v);
        val[v] += val[edge[u].to];
    }
    fat[v][0] = fa;
    for (long long i = 1; (1 << i) < deep[i]; ++i) {
        fat[v][i] = fat[fat[v][i - 1]][i - 1];
    }
}
inline void dfs2(long long v, long long fa) {
    if (v != fa && fat[v][0] != 1) {
        ava[v] = ava[fa] + val[v];
    }
    for (long long u = head[v]; u; u = edge[u].next) {
        if (edge[u].to == fa) {
            continue;
        }
        dfs2(edge[u].to, v);
    }
}
inline long long lca(long long x, long long y) {
    x = undfn[x];
    y = undfn[y];
    if (deep[x] < deep[y]) {
        std::swap(x, y);
    }
    while (deep[x] > deep[y]) {
        x = fat[x][lg[deep[x] - deep[y]] - 1];
    }
    if (x == y) {
        return x;
    }
    for(long long k = lg[deep[x]] - 1; k >= 0; k--) {
        if (fat[x][k] != fat[y][k]) {
            x = fat[x][k];
            y = fat[y][k];
        }
    }
    return dfn[fat[x][0]];
}