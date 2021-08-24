#include <bits/stdc++.h>

inline void ios(std::string s) {
    std::string t;
    freopen((s + ".in").data(), "r", stdin);
    freopen((s + ".out").data(), "w", stdout);
}

const int N = 100005;
const int P = 998244353;

int T, n, x, y;

inline int Main() {
    std::cin >> n >> x;
    if (n == 1) return std::cout << x << std::endl, 0;
    std::cin >> y, std::cout << (x + P - y) % P << std::endl;
    for (int i = 2; i < n; ++i) std::cin >> x;
    return 0;
}

int main() {
    ios("aminusb");
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> T;
    while (T--) Main();
    return 0;
}