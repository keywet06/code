#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::map<int, std::vector<int> > Map;
    for (int i = 1, x; i <= n; ++i) std::cin >> x, Map[x].push_back(i);
    int x, k;
    while (q--) {
        std::cin >> x >> k;
        if (!Map.count(x) || Map[x].size() < k) {
            std::cout << -1 << '\n';
        } else {
            std::cout << Map[x][k - 1] << '\n';
        }
    }
    return 0;
}