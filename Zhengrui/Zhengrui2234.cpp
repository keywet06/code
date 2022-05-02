#include <bits/stdc++.h>

const int N = 200005;

int n, q, x, y, z;
int a[N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> q;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    for (int i = 1; i < n; ++i) std::cin >> x >> y;
    while (q--) {
        std::cin >> x >> y;
        a[x] = y;
        std::cout << (n == 2 && a[1] == a[2] ? "Yes" : "No") << '\n';
    }
    return 0;
}