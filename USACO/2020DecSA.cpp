#include <bits/stdc++.h>

const int N = 100005;

int n, x, y, ans;
int deg[N], ls[N];

int main() {
    std::cin >> n, deg[1] = 1;
    for (int i = 1; i < n; ++i) std::cin >> x >> y, ++deg[x], ++deg[y];
    for (int i = 0; 1 << i < N; ++i) {
        for (int j = (1 << i) + 1; j <= 1 << (i + 1), j < N; ++j) ls[j] = i + 1;
    }
    for (int i = 1; i <= n; ++i) ans += deg[i] - 1 + ls[deg[i]];
    std::cout << ans << std::endl;
    return 0;
}