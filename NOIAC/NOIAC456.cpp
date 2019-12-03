#include <bits/stdc++.h>
class data {
    public:
        long long val, id;
};
const int N = 1000005;
data tp;
data max[N];
int CLOCK, cnt, n, k, x, y;
int next[N], head[N], to[N], dfn[N], und[N], fa[N], lst[N];
long long ans;
long long val[N], plus[N];
int operator < (data, data);
void insert(int, int);
void dfs(int);
void build(int, int, int);
void pushdown(int);
void update(int);
void update(int, int, int, int, int, int);
data query(int, int, int, int, int);
int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &val[i]);
    }
    for (int i = 1; i < n; ++i) {
        scanf("%d %d", &x, &y);
        insert(x, y);
        fa[y] = x;
    }
    build(1, 1, n);
    dfs(1);
    for (int i = 1; i <= k; ++i) {
        tp = query(1, 1, n, 1, n);
        x = und[tp.id];
        ans += tp.val;
        while (val[x]) {
            update(1, 1, n, dfn[x], lst[x], -val[x]);
            val[x] = 0;
            x = fa[x];
        }
    }
    printf("%lld\n", ans);
    return 0;
}
inline int operator < (data x, data y) {
    return x.val < y.val;
}
inline void insert(int x, int y) {
    ++cnt;
    next[cnt] = head[x];
    head[x] = cnt;
    to[cnt] = y;
}
inline void dfs(int v) {
    dfn[v] = ++CLOCK;
    und[CLOCK] = v;
    for (int u = head[v]; u; u = next[u]) {
        dfs(to[u]);
    }
    lst[v] = CLOCK;
    update(1, 1, n, dfn[v], lst[v], val[v]);
}
inline void build(int v, int l, int r) {
    max[v].id = l;
    if (l == r) {
        return;
    }
    int mid = (l + r) >> 1;
    build(v << 1, l, mid);
    build(v << 1 | 1, mid + 1, r);
}
inline void pushdown(int v) {
    plus[v << 1] += plus[v];
    plus[v << 1 | 1] += plus[v];
    max[v << 1].val += plus[v];
    max[v << 1 | 1].val += plus[v];
    plus[v] = 0;
}
inline void update(int v) {
    max[v] = std::max(max[v << 1], max[v << 1 | 1]);
}
inline void update(int v, int l, int r, int x, int y, int z) {
    if (x <= l && r <= y) {
        plus[v] += z;
        max[v].val += z;
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(v);
    if (x <= mid) {
        update(v << 1, l, mid, x, y, z);
    }
    if (y > mid) {
        update(v << 1 | 1, mid + 1, r, x, y, z);
    }
    update(v);
}
inline data query(int v, int l, int r, int x, int y) {
    if (x <= l && r <= y) {
        return max[v];
    }
    int mid = (l + r) >> 1;
    data tmp = {-1, 0};
    pushdown(v);
    if (x <= mid) {
        tmp = std::max(tmp, query(v << 1, l, mid, x, y));
    }
    if (y > mid) {
        tmp = std::max(tmp, query(v << 1 | 1, mid + 1, r, x, y));
    }
    return tmp;
}