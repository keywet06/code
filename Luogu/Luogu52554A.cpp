#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    int Ans = 0;
    for (int i = 0, x; i < n; ++i) std::cin >> x, Ans += std::min(a[i], x);
    std::cout << Ans << std::endl;
    return 0;
}