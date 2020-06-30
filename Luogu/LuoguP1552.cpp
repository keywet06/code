#include <bits/stdc++.h>
const int N = 100005;
struct node {
    int l, r, v, t, f, s, h, e, d; // ls, rs, val, top, fa, size, sum, lead, dis
};
int n, m, x;
long long ans;
node d[N];
int merge(int a, int b) {
    if (!a || !b) return a + b;
    if (d[a].v < d[b].v) std::swap(a, b);
    d[a].r = merge(d[a].r, b);
    d[d[a].l].t = d[d[a].r].t = d[a].t = a;
    d[a].h = d[d[a].l].h + d[d[a].r].h;
    d[a].s = d[d[a].l].s + d[d[a].r].s;
    if (d[d[a].l].d < d[d[a].r].d) std::swap(d[a].l, d[a].r);
    d[a].d = d[d[a].r].d + 1;
    return a;
}
int t(int x) { return d[x].t == x ? x : d[x].t = t(d[x].t); }
int pop(int x) {
    d[d[x].l].t = d[x].l;
    d[d[x].r].t = d[x].r;
    return d[x].t = merge(d[x].l, d[x].r);
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        std::cin >> d[i].f >> d[i].v >> d[i].e;
        d[i].h = d[i].v;
        d[i].e = std::max(d[i].e, d[d[i].f].e);
        d[i].t = i;
        d[i].s = 1;
    }
    d[0].d = -1;
    for (int i = n; i; --i) {
        ans = std::max(ans, 1ll * d[t(i)].s * d[i].e);
        merge(d[i].f, x = t(i));
        while (d[x].h > m) x = pop(x);
    }
    std::cout << ans << std::endl;
    return 0;
}