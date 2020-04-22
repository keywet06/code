#include <bits/stdc++.h>
const int N = 30005;
int n, m, x, y;
int ex[N], ey[N];
std::set<int> set[N];
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 1; i < n; ++i) {
        std::cin >> ex[i] >> ey[i];
        set[i].insert(i);
    }
    set[n].insert(n);
    for (int i = 1; i <= m; ++i) {
        std::cin >> x >> y;
        if (x == 1) {
            int ans = 0;
            for (int i = 1; i <= n; ++i) {
                ans += set[i].count(y);
            }
            std::cout << ans << "\n";
        } else {
            set[ex[y]].insert(set[ey[y]].begin(), set[ey[y]].end());
            set[ey[y]] = set[ex[y]];
        }
    }
    return 0;
}