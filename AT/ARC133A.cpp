#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> a(n + 1);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    int x = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] > a[i + 1]) {
            x = a[i];
            break;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (a[i] != x) std::cout << a[i] << ' ';
    }
    std::cout << std::endl;
    return 0;
}