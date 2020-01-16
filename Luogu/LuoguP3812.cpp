#include <bits/stdc++.h>
const int T = 50;
const int Tp = T + 5;
long long ans, n, x;
long long asd[Tp];
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> x;
        for (int j = T; ~j; --j) {
            if ((x >> j) & 1) {
                if (!asd[j]) {
                    asd[j] = x;
                    break;
                } else {
                    x ^= asd[j];
                }
            }
        }
    }
    for (int j = T; ~j; --j) {
        if (!((ans >> j) & 1)) {
            ans ^= asd[j];
        }
    }
    std::cout << ans << std::endl;
    return 0;
}