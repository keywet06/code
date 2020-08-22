#include <bits/stdc++.h>
const int N = 50005;
const int S = 224;
class query {
   public:
    int l, r, id;
};
int n, m, l, r;
int a[N];
long long ans, k;
long long al[N], ar[N], c[N];
query q[N];
inline int id(int x) { return x / S; }
inline int operator<(query x, query y) {
    return id(x.l) == id(y.l) ? x.r < y.r : x.l < y.l;
}
inline void change(int x, int d) {
    ans -= c[x] * (c[x] - 1) / 2;
    c[x] += d;
    ans += c[x] * (c[x] - 1) / 2;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    for (int i = 0; i < m; ++i) std::cin >> q[i].l >> q[i].r, q[i].id = i;
    std::sort(q, q + m);
    l = 1;
    for (int i = 0; i < m; ++i) {
        while (l < q[i].l) change(a[l++], -1);
        while (l > q[i].l) change(a[--l], 1);
        while (r < q[i].r) change(a[++r], 1);
        while (r > q[i].r) change(a[r--], -1);
        al[q[i].id] = ans;
        ar[q[i].id] = (r - l + 1ll) * (r - l) / 2;
        if (!al[q[i].id]) {
            ar[q[i].id] = 1;
        } else {
            k = std::__gcd(al[q[i].id], ar[q[i].id]);
            al[q[i].id] /= k;
            ar[q[i].id] /= k;
        }
    }
    for (int i = 0; i < m; ++i) std::cout << al[i] << '/' << ar[i] << '\n';
    return 0;
}