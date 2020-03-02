#include <bits/stdc++.h>
long long m, n, x, y;
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        std::cin >> x >> y;
    }
    std::cout << std::fixed << std::setprecision(10);
    for (int i = 1; i <= m; ++i) {
        std::cin >> x >> y;
        std::cout << sqrt(x * x + y * y) << std::endl;
    }
    return 0;
}