#include <bits/stdc++.h>

using int64 = long long;

int n, t;

int64 c;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> t;
    if (t == 1) {
        if (n == 1) {
            std::cout << 1 << std::endl;
        } else if (n == 2) {
            std::cout << -1 << std::endl;
        } else if (n & 1) {
            for (int i = 1; i <= n - 2; ++i) std::cout << 1 << ' ';
            std::cout << 2 << ' ' << n << std::endl;
        } else {
            for (int i = 1; i <= n - 3; ++i) std::cout << 1 << ' ';
            std::cout << 2 << ' ' << 2 << ' ' << n + 1 << std::endl;
        }
    } else {
        if (n == 1) {
            std::cout << "1" << std::endl;
        } else if (n == 2) {
            std::cout << "-1" << std::endl;
        } else if (n == 3) {
            std::cout << "1 2 3" << std::endl;
        } else if (n == 4) {
            std::cout << "1 2 6 9" << std::endl;
        } else if (n == 5) {
            std::cout << "1 2 4 7 14" << std::endl;
        } else if (n == 6) {
            std::cout << "1 2 3 4 6 8" << std::endl;
        } else {
            n -= 5;
            std::cout << (1ll << (n)) * 2 << ' ' << (1ll << (n)) * 3 << ' '
                      << (1ll << (n)) * 4 << ' ' << (1ll << (n)) * 6 << ' '
                      << (1ll << (n)) * 8 << ' ' << 3 << ' ' << 1;
            for (int i = 2; i <= n - 1; i++) std::cout << ' ' << (1ll << i);
            std::cout << std::endl;
        }
    }
    return 0;
}