#include <bits/stdc++.h>

using int64 = long long;

int64 n, m, x;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> m;
    while (!(x * m / n)) ++x;
    for (int i = x; i < n; ++i) std::cout << i * m / n << ' ';
    while (x--) std::cout << m << ' ';
    std::cout << std::endl;
    return 0;
}