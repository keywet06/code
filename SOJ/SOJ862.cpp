#include <bits/stdc++.h>
const int mod = 998244353;
int n, k;
int main() {
    std::cin >> n >> k;
    if (k == 1) {
        std::cout << 1 << std::endl;
    } else if (k == 2) {
        std::cout << n / 2 << std::endl;
    } else if (k == 3) {
        std::cout << ((n - 1ll) * (n - 2) / 2 - (n - 1) / 2 * 3 +
                      2 * (n % 3 == 0) + (2 * n - 1ll) * (2 * n - 2) / 2 -1) / 6 %
                         mod
                  << std::endl;
    }
    return 0;
}