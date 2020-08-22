#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
const int N = 300000;
const int S = 400;
int n, l, r, opt, ans;
long long c;
long long a[N], up[N], tag[N];
inline int id(int x) { return x / S; }
inline int begins(int x) { return id(x) * S; }
inline int ends(int x) { return id(x) * S + S; }
inline void pushdown(int x) {
    if (!tag[id(x)]) return;
    for (register int i = begins(x); i < ends(x); ++i) a[i] = up[id(i)];
    tag[id(x)] = 0;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    memset(a, 127, sizeof(a));
    std::cin >> n;
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    while (n--) {
        register int i, j;
        std::cin >> l >> r >> c;
        --l, --r;
        ans = 0;
        pushdown(l);
        pushdown(r);
        if (id(l) == id(r)) {
            for (i = l; i <= r; ++i) ans += a[i] == c, a[i] = c;
            std::cout << ans << '\n';
            continue;
        }
        for (i = l; i < ends(l); ++i) ans += a[i] == c, a[i] = c;
        for (i = begins(r); i <= r; ++i) ans += a[i] == c, a[i] = c;
        for (i = l / S + 1; i < r / S; ++i) {
            if (tag[i]) {
                ans += S * (c == up[i]);
            } else {
                for (j = i * S; j < i * S + S; ++j) {
                    ans += a[j] == c;
                    a[j] = c;
                }
            }
            tag[i] = 1, up[i] = c;
        }
        std::cout << ans << '\n';
    }
    return 0;
}