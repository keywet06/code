#include <bits/stdc++.h>

const int B = 2;
const int N = 300005;

struct node {
    int f, v, s[B], l;
};

int n, l, r, c, r, s, t, x;

node d[N];

int gt(int u) { return u == d[d[u].f].s[1]; }

void pushdown(int u) {
    if (!d[u].l) return;
    if (s = d[u].s[0]) d[s].v += d[u].l, d[s].l += d[u].l;
    if (s = d[u].s[1]) d[s].v += d[u].l, d[s].l += d[u].l;
    d[u].l = 0;
}

void rotate(int u) {
    t = gt(u), pushdown(d[u].f), pushdown(u);
    if (d[d[u].f].s[t] = d[u].s[!t]) d[d[u].s[!t]].f = d[u].f;
    d[u].s[!t] = d[u].f;
    if (d[u].f = d[d[u].f].f) d[d[u].f].s[gt(d[u].s[!t])] = u;
    d[d[u].s[!t]].f = u;
    if (!d[u].f) r = u;
}

void splay(int u) {
    while (d[u].f) {
        if (!d[d[u].f].f) return rotate(u);
        rotate(gt(u) == gt(d[u].f) ? d[u].f : u), rotate(u);
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    r = c = 1;
    for (int i = 1; i <= n; ++i) {
        std::cin >> l >> r;
    }
    return 0;
}