#include <bits/stdc++.h>
const int N = 300005;
int n, m, x;
int rt[N], ls[N], rs[N], ds[N], fa[N], kd[N], de[N], nm[N], si[N];
long long mt[N], pt[N], val[N], ha[N], dh[N];
inline void pushdown(int u) {
    if (ls[u]) {
        mt[ls[u]] *= mt[u];
        (pt[ls[u]] *= mt[u]) += pt[u];
        (val[ls[u]] *= mt[u]) += pt[u];
    }
    if (rs[u]) {
        mt[rs[u]] *= mt[u];
        (pt[rs[u]] *= mt[u]) += pt[u];
        (val[rs[u]] *= mt[u]) += pt[u];
    }
    pt[u] = 0;
    mt[u] = 1;
}
inline int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (val[x] > val[y]) std::swap(x, y);
    pushdown(x);
    rs[x] = merge(rs[x], y);
    if (ds[ls[x]] < ds[rs[x]]) std::swap(ls[x], rs[x]);
    ds[x] = ds[rs[x]] + 1;
    return x;
}
inline int pop(int u) {
    pushdown(u);
    return merge(ls[u], rs[u]);
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m;
    ha[0] = 1;
    for (int i = 1; i <= n; ++i) std::cin >> ha[i];
    kd[1] = de[1] = 1;
    for (int i = 2; i <= n; ++i) {
        std::cin >> fa[i] >> kd[i] >> dh[i];
        de[i] = de[fa[i]] + 1;
    }
    for (int i = 1; i <= m; ++i) {
        std::cin >> val[i] >> x;
        rt[x] = merge(rt[x], i);
        nm[i] = de[x];
        mt[i] = 1;
    }
    for (int i = n; ~i; --i) {
        while (rt[i] && val[rt[i]] < ha[i]) {
            nm[rt[i]] -= de[i];
            ++si[i];
            rt[i] = pop(rt[i]);
        }
        if (rt[i] && i) {
            if (kd[i]) {
                mt[rt[i]] *= dh[i];
                pt[rt[i]] *= dh[i];
                val[rt[i]] *= dh[i];
            } else {
                pt[rt[i]] += dh[i];
                val[rt[i]] += dh[i];
            }
            rt[fa[i]] = merge(rt[fa[i]], rt[i]);
        }
    }
    for (int i = 1; i <= n; ++i) std::cout << si[i] << '\n';
    for (int i = 1; i <= m; ++i) std::cout << nm[i] << '\n';
    return 0;
}