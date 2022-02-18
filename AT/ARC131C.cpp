#include <bits/stdc++.h>

const int N = 400005;

int n, s;
int a[N];

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> a[i], s ^= a[i];
    if (n & 1) return std::cout << "Win" << '\n', 0;
    for (int i = 1; i <= n; ++i) {
        if (s == a[i]) return std::cout << "Win" << '\n', 0;
    }
    std::cout << "Lose" << '\n';
    return 0;
}
