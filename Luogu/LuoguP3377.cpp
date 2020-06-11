#include <bits/stdc++.h>
const int N = 100005;
class node;
extern int is[];
extern node nd[];
class node {
   public:
    int l, r, f, v, d, t, p;
    void update() {
        if (nd[l].d < nd[r].d) {
            std::swap(l, r);
        }
        d = nd[r].d + 1;
    }
};
int n, m, opt, x, y;
int is[N];
node nd[N];
int t(int x) { return nd[x].t == x ? x : nd[x].t = t(nd[x].t); }
int merge(int a, int b) {
    if (!a || !b) return a + b;
    if (nd[a].v > nd[b].v || nd[a].v == nd[b].v && a > b) std::swap(a, b);
    nd[a].r = merge(nd[a].r, b);
    nd[nd[a].r].t = nd[nd[a].r].f = a;
    nd[a].update();
    return a;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        std::cin >> nd[i].v;
        nd[i].t = i;
        is[i] = 1;
    }
    nd[0].d = -1;
    for (int i = 1; i <= m; ++i) {
        std::cin >> opt;
        if (opt == 1) {
            std::cin >> x >> y;
            if (is[x] && is[y] && t(x) != t(y)) {
                merge(x, y);
            }
        } else {
            std::cin >> x;
            if (is[x]) {
                x = t(x);
                std::cout << nd[x].v << '\n';
                is[x] = 0;
                nd[x].t = nd[x].l;
                nd[x].l = nd[x].l;
                nd[x].r = nd[x].r;
                nd[nd[x].l].f = nd[nd[x].r].f = 0;
                merge(nd[x].l, nd[x].r);
            } else {
                std::cout << -1 << '\n';
            }
        }
    }
    return 0;
}
