#include <bits/stdc++.h>

using float96 = long double;

const float96 opt = 1e-6;
const float96 Cu = 63.55;

int k;

float96 le, m, n, la, ans;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cout << std::fixed << std::setprecision(8);
    std::cin >> le >> k;
    while (k--) {
        std::cin >> m >> n, n *= Cu;
        if (le - m + opt < n) return std::cout << "Impossible" << std::endl, 0;
        ans += n, le = m;
    }
    std::cout << ans / Cu << ' ' << (ans + le) / Cu << std::endl;
    return 0;
}