#include <bits/stdc++.h>
const int N = 200005;
const int S = 400;
const int mod = 10007;
int n, opt, l, r, c;
long long ans;
long long a[N], plus[N], mult[N];
inline int id(int x) { return x / S; }
inline int begins(int x) { return id(x) * S; }
inline int ends(int x) { return id(x) * S + S; }
inline void pushdown(int x) {
    for (int i = begins(x); i < ends(x); ++i) {
        a[i] = (a[i] * mult[id(x)] + plus[id(x)]) % mod;
    }
    mult[id(x)] = 1;
    plus[id(x)] = 0;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        mult[i] = 1;
    }
    for (int i = 1; i <= n; ++i) {
        std::cin >> opt >> l >> r >> c;
        --l, --r;
        if (opt == 0) {
            if (id(l) == id(r)) {
                pushdown(l);
                for (int i = l; i <= r; ++i) a[i] = (a[i] + c) % mod;
                continue;
            }
            pushdown(l);
            pushdown(r);
            for (int i = l; i < ends(l); ++i) a[i] = (a[i] + c) % mod;
            for (int i = begins(r); i <= r; ++i) a[i] = (a[i] + c) % mod;
            for (int i = id(l) + 1; i < id(r); ++i) {
                plus[i] = (plus[i] + c) % mod;
            }
        } else if (opt == 1) {
            if (id(l) == id(r)) {
                pushdown(l);
                for (int i = l; i <= r; ++i) a[i] = a[i] * c % mod;
                continue;
            }
            pushdown(l);
            pushdown(r);
            for (int i = l; i < ends(l); ++i) a[i] = a[i] * c % mod;
            for (int i = begins(r); i <= r; ++i) a[i] = a[i] * c % mod;
            for (int i = id(l) + 1; i < id(r); ++i) {
                plus[i] = plus[i] * c % mod;
                mult[i] = mult[i] * c % mod;
            }
        } else {
            pushdown(r);
            std::cout << a[r] << '\n';
        }
    }
    return 0;
}