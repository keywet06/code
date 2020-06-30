#include <bits/stdc++.h>
const int N = 100005;
class node;
extern node nd[];
struct node {
    int l, r, v, d, t;
};
int n, m, opt, x, y;
node nd[N];
int t(int x) { return nd[x].t == x ? x : nd[x].t = t(nd[x].t); }
int merge(int a, int b) {
    if (!a || !b) return a + b;
    if (nd[a].v > nd[b].v || nd[a].v == nd[b].v && a > b) std::swap(a, b);
    nd[a].r = merge(nd[a].r, b);
    nd[nd[a].l].t = nd[nd[a].r].t = nd[a].t = a;
    if (nd[nd[a].l].d < nd[nd[a].r].d) std::swap(nd[a].l, nd[a].r);
    nd[a].d = nd[nd[a].r].d + 1;
    return a;
}
void pop(int x) {
    nd[x].v = 0;
    nd[nd[x].l].t = nd[x].l;
    nd[nd[x].r].t = nd[x].r;
    nd[x].t = merge(nd[x].l, nd[x].r);
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        std::cin >> nd[i].v;
        nd[i].t = i;
    }
    nd[0].d = -1;
    for (int i = 1; i <= m; ++i) {
        std::cin >> opt;
        if (opt == 1) {
            std::cin >> x >> y;
            if (!(nd[x].v && nd[y].v)) continue;
            x = t(x), y = t(y);
            if (x != y) merge(x, y);
        } else {
            std::cin >> x;
            if (nd[x].v) {
                x = t(x);
                std::cout << nd[x].v << '\n';
                pop(x);
            } else {
                std::cout << -1 << '\n';
            }
        }
    }
    return 0;
}
