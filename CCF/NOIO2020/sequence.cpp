#include <bits/stdc++.h>
int T, a1, a2, t, x;
int main() {
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> T;
    while (T--) {
        std::cin >> a1 >> a2;
        if (a1 != 2 || a2 != 1) {
            x = 0;
            while (a1--) {
                std::cin >> t;
                x ^= t;
                std::cin >> t;
                x ^= t;
            }
            while (a2--) {
                std::cin >> t >> t >> t;
            }
            puts(x & 1 ? "NO" : "YES");
            continue;
        }
        std::cin >> a1 >> a2;
        std::cin >> t;
        a1 -= t;
        std::cin >> t;
        a2 -= t;
        std::cin >> t >> t >> t;
        puts(a1 == (t == 1 ? a2 : -a2) ? "YES" : "NO");
    }
    return 0;
}