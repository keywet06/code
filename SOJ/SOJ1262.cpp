#include <bits/stdc++.h>

using int64 = long long;

int64 T, n, k, c, d;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> T;
    while (T--) {
        std::cin >> n >> k;
        d = n / k, c = n % k;
        if (d > 1) {
            if (k & 1) {
                if (c & 1) {
                    std::cout << d + 1 << '\n';
                } else {
                    if (c) {
                        std::cout << d + 2 << '\n';
                    } else {
                        std::cout << d << '\n';
                    }
                }
            } else {
                if (c & 1) {
                    std::cout << -1 << '\n';
                } else {
                    if (c) {
                        std::cout << d + 1 << '\n';
                    } else {
                        std::cout << d << '\n';
                    }
                }
            }
        } else {
            if (c & 1) {
                if (k & 1) {
                    std::cout << (n + 2 * c - 1) / (2 * c) * 2 << '\n';
                } else {
                    std::cout << -1 << '\n';
                }
            } else {
                if (c) {
                    std::cout << 3 << '\n';
                } else {
                    std::cout << 1 << '\n';
                }
            }
        }
    }
    return 0;
}