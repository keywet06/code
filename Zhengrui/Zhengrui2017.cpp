#include <bits/stdc++.h>

const int N = 100005;

int n, m, l, r, x, y, ans;
int a[N];

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    for (int _ = 1; _ <= m; ++_) {
        std::cin >> l >> r >> x, ans = 0;
        for (int i = l; i <= r; ++i) ans += std::__gcd(a[i], x) == 1;
        std::cout << ans << '\n';
    }
    return 0;
}