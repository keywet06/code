#include <bits/stdc++.h>

int T, n, m;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> T;
    while (T--) {
        std::cin >> n >> m;
        for (int i = 1; i <= m; ++i) std::cout << (i & 1);
        std::cout << '\n';
        for (int i = 2; i < n; ++i) {
            std::cout << (i & 1);
            for (int j = 2; j < m; ++j) std::cout << 0;
            std::cout << (i & 1) << '\n';
        }
        if (n & 1) {
            for (int i = 1; i <= m; ++i) std::cout << (i & 1);
        } else {
            if (n == 3) {
                std::cout << "000";
            } else {
                std::cout << "00";
                for (int i = 5; i <= m; ++i) std::cout << (i & 1);
                std::cout << "00";
            }
        }
        std::cout << "\n\n";
    }
    return 0;
}