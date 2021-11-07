#include <bits/stdc++.h>

auto gcd = std::__gcd<int>;

int n, x, y, max, idx;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        if (gcd(i, n) > 1) continue;
        x = i, y = 1;
        while (x > 1) x = x * i % n, ++y;
        if (y > max) max = y, idx = i;
    }
    x = 1, y = n * (n - 1);
    for (int i = 1; i < n; ++i) {
        x = x * idx % n;
        std::cout << ((i * n - x * (n - 1)) % y + y) % y << ' ';
    }
    std::cout << '\n';
    return 0;
}