#include <bits/stdc++.h>
const int N = 50005;
const int S = 224;
class query {
   public:
    int l, r, id;
};
int n, m, k, l, r;
int a[N], c[N];
long long ans;
long long aa[N];
query q[N];
inline int id(int x) { return x / S; }
inline int operator<(query x, query y) {
    return id(x.l) == id(y.l) ? x.r < y.r : x.l < y.l;
}
inline void change(int x, int d) {
    ans -= c[x] * c[x];
    c[x] += d;
    ans += c[x] * c[x];
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    for (int i = 0; i < m; ++i) std::cin >> q[i].l >> q[i].r, q[i].id = i;
    std::sort(q, q + m);
    l = 1;
    for (int i = 0; i < m; ++i) {
        while (l < q[i].l) change(a[l++], -1);
        while (l > q[i].l) change(a[--l], 1);
        while (r < q[i].r) change(a[++r], 1);
        while (r > q[i].r) change(a[r--], -1);
        aa[q[i].id] = ans;
    }
    for (int i = 0; i < m; ++i) std::cout << aa[i] << '\n';
    return 0;
}