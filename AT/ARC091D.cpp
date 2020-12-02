#include <bits/stdc++.h>

int n, ans, a, k;

int dfs(int a, int x) {
    if (a < x) return 0;
    if (a % x == 0) return a / x;
    int t = a / x, h = a % x;
    return dfs(a - ((h - 1) / (t + 1) + 1) * (t + 1), x);
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> a >> k, ans ^= dfs(a, k);
    std::cout << (ans ? "Takahashi" : "Aoki") << std::endl;
    return 0;
}