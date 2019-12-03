#include <bits/stdc++.h>
const int M = 200005;
const int N = 100005;
const int mod = 1000000007;
int cnt, n, x, y;
int next[M], to[M];
int head[N], fa[N], size[N];
long long ans;
long long jc[N], a[N], in[N];
void insert(int, int);
void addedge(int, int);
long long exgcd(long long, long long, long long &, long long &);
long long inv(long long);
void update(int);
void dfs1(int, int);
void dfs2(int, int);
int main() {
    scanf("%d", &n);
    jc[0] = 1;
    for (register int i = 1; i <= n; ++i) {
        jc[i] = jc[i - 1] * i % mod;
    }
    in[0] = 1;
    for (register int i = 1; i <= n; ++i) {
        in[i] = in[i - 1] * inv(i) % mod;
    }
    for (register int i = 1; i < n; ++i) {
        scanf("%d %d", &x, &y);
        addedge(x, y);
    }
    dfs1(1, 1);
    dfs2(1, 1);
    printf("%lld\n", ans);
    return 0;
}
inline void insert(int x, int y) {
    ++cnt;
    next[cnt] = head[x];
    head[x] = cnt;
    to[cnt] = y;
}
inline void addedge(int x, int y) {
    insert(x, y);
    insert(y, x);
}
inline long long exgcd(long long a, long long b,
    long long &x, long long &y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    int tmp = exgcd(b, a % b, x, y);
    std::swap(x, y);
    y = y - x * (a / b);
    return tmp;
}
inline long long inv(long long a) {
    long long x, y;
    exgcd(a, mod, x, y);
    return (x % mod + mod) % mod;
}
inline void update(int v) {
    static int tmp;
    a[v] = jc[size[v] - 1];
    for (register int u = head[v]; u; u = next[u]) {
        if (to[u] == fa[v]) {
            continue;
        }
        (a[v] *= a[to[u]]) %= mod;
        (a[v] *= in[size[to[u]]]) %= mod;
    }
}
inline void dfs1(int v, int f) {
    fa[v] = f;
    size[v] = 1;
    for (register int u = head[v]; u; u = next[u]) {
        if (to[u] == fa[v]) {
            continue;
        }
        dfs1(to[u], v);
        size[v] += size[to[u]];
    }
    update(v);
}
inline void dfs2(int v, int f) {
    (ans += a[v]) %= mod;
    int ta, tb;
    for (register int u = head[v]; u; u = next[u]) {
        if (to[u] == f) {
            continue;
        }
        fa[v] = fa[to[u]] = to[u];
        size[v] = n - size[to[u]];
        size[to[u]] = n;
        ta = a[v];
        tb = a[to[u]];
        (a[v] *= in[n - 1] * jc[size[v] - 1] % mod * jc[n - size[v]] % mod * inv(a[to[u]]) % mod) %= mod;
        (a[to[u]] *= in[n - size[v] - 1] * jc[n - 1] % mod * in[size[v]] % mod * a[v] % mod) %= mod;
        dfs2(to[u], v);
        fa[v] = fa[to[u]] = v;
        size[to[u]] = n - size[v];
        size[v] = n;
        a[v] = ta;
        a[to[u]] = tb;
    }
}