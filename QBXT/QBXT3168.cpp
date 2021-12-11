#include <bits/stdc++.h>

int x, k;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> x >> k;
    for (int i = 1; i < k; ++i) std::cout << i << ' ' << 0 << '\n';
    std::cout << x - k + 1 << ' ' << 1 << '\n';
    return 0;
}