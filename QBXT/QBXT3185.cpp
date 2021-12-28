#include <bits/stdc++.h>

using int64 = long long;
using float128 = long double;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    int64 n;
    std::cin >> n;
    std::cout << std::fixed << std::setprecision(9);
    std::cout << float128(n + 1) * n / (4 * n - 2) << std::endl;
    return 0;
}