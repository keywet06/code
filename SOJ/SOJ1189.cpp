#include <bits/stdc++.h>

const int N = 1000005;

int n;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i < n; ++i) {
        std::cout << i << ' ' << i + 1 << ' ' << 2 * i << '\n';
    }
    std::cout << 2 * N << ' ' << 1 << ' ' << 2 * N << std::endl;
    return 0;
}