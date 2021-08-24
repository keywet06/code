#include <bits/stdc++.h>

#define fir first
#define sec second
#define mkp std::make_pair
#define pub push_back
#define pus push
#define pob pop_back

using db = double;
using int32 = int;
using int64 = long long;
using i5 = int32;
using pi5db = std::pair<i5, db>;
using pi5pi5db = std::pair<i5, pi5db>;

namespace oct {

inline void ios(int x = 8) {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cout << std::showpoint << std::setprecision(x) << std::fixed;
}

}  // namespace oct

const int N = 200005;
const int Np = 524288;

double sus[Np], suc[Np];

int o, n, m, l, r, v;
int a[N];

int64 plus[Np];

inline void tlus(int u, int64 x, double s, double c) {
    static double si, cs;
    si = sus[u], cs = suc[u], plus[u] += x;
    sus[u] = si * c + cs * s, suc[u] = cs * c - si * s;
}

inline void pushdown(int u) {
    if (!plus[u]) return;
    static double si, cs;
    si = sin(plus[u]), cs = cos(plus[u]);
    tlus(u << 1, plus[u], si, cs), tlus(u << 1 | 1, plus[u], si, cs);
    plus[u] = 0;
}

inline void pushup(int u) {
    sus[u] = sus[u << 1] + sus[u << 1 | 1];
    suc[u] = suc[u << 1] + suc[u << 1 | 1];
}

inline void build(int u, int l, int r) {
    if (l == r) return sus[u] = sin(a[l]), suc[u] = cos(a[l]), void(0);
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

inline void update(int u, int l, int r, int x, int y, int z, double s,
                   double c) {
    if (l >= x && r <= y) return tlus(u, z, s, c);
    int mid = l + r >> 1;
    pushdown(u);
    if (x <= mid) update(u << 1, l, mid, x, y, z, s, c);
    if (y > mid) update(u << 1 | 1, mid + 1, r, x, y, z, s, c);
    pushup(u);
}

inline double query(int u, int l, int r, int x, int y) {
    if (l >= x && r <= y) return sus[u];
    int mid = l + r >> 1;
    double ret = 0;
    pushdown(u);
    if (x <= mid) ret += query(u << 1, l, mid, x, y);
    if (y > mid) ret += query(u << 1 | 1, mid + 1, r, x, y);
    return ret;
}

int main() {
    oct::ios(1);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    build(1, 1, n);
    std::cin >> m;
    while (m--) {
        std::cin >> o >> l >> r;
        if (o == 1) std::cin >> v, update(1, 1, n, l, r, v, sin(v), cos(v));
        if (o == 2) std::cout << query(1, 1, n, l, r) << '\n';
    }
    return 0;
}