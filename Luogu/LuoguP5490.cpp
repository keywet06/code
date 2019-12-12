#include <bits/stdc++.h>
const int N = 100005;
const int L = 400005;
const int XL = 800005;
class Mt {
   public:
    int x1, x2, y1, y2;
};
class Sr {
   public:
    int x, l, r, opt;
};
class Nd {
   public:
    int g, f, s;
};
int cnt, pnt, n;
int lsh[L];
long long ans;
Mt mt[N];
Nd nd[XL];
Sr sr[L];
int operator<(Sr, Sr);
void pushup(int);
void build(int = 1, int = 1, int = cnt);
void update(int, int, int, int = 1, int = 1, int = cnt);
inline int operator<(Sr x, Sr y) {
    return x.x < y.x;
}
inline void pushup(int v) {
    nd[v].s = nd[v].f ? nd[v].g : nd[v << 1].s + nd[v << 1 | 1].s;
}
inline void build(int v, int l, int r) {
    if (l == r) {
        nd[v].g = lsh[l] - lsh[l - 1];
        return;
    }
    int mid = l + r >> 1;
    build(v << 1, l, mid);
    build(v << 1 | 1, mid + 1, r);
    nd[v].g = nd[v << 1].g + nd[v << 1 | 1].g;
}
inline void update(int x, int y, int z, int v, int l, int r) {
    if (x <= l && r <= y) {
        nd[v].f += z;
        pushup(v);
        return;
    }
    int mid = l + r >> 1;
    if (x <= mid) {
        update(x, y, z, v << 1, l, mid);
    }
    if (y > mid) {
        update(x, y, z, v << 1 | 1, mid + 1, r);
    }
    pushup(v);
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> mt[i].x1 >> mt[i].y1 >> mt[i].x2 >> mt[i].y2;
        lsh[cnt++] = mt[i].x1;
        lsh[cnt++] = mt[i].x2;
    }
    std::sort(lsh, lsh + cnt);
    cnt = std::unique(lsh, lsh + cnt) - lsh;
    for (int i = 1; i <= n; ++i) {
        mt[i].x1 = std::lower_bound(lsh, lsh + cnt, mt[i].x1) - lsh;
        mt[i].x2 = std::lower_bound(lsh, lsh + cnt, mt[i].x2) - lsh;
        sr[++pnt] = {mt[i].y1, mt[i].x1 + 1, mt[i].x2, 1};
        sr[++pnt] = {mt[i].y2, mt[i].x1 + 1, mt[i].x2, -1};
    }
    std::sort(sr + 1, sr + 1 + pnt);
    build();
    for (int i = 1; i <= n << 1; ++i) {
        ans += 1ll * (sr[i].x - sr[i - 1].x) * nd[1].s;
        update(sr[i].l, sr[i].r, sr[i].opt);
    }
    std::cout << ans << std::endl;
    return 0;
}