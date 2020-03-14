#include <bits/stdc++.h>
const int N = 100005;
int n, m, q, p, x, y, z;
std::set<short int> dp[N];
std::vector<std::pair<int, int> > out[N];
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m >> q >> p;
    for (int i = 1; i <= m; ++i) {
        std::cin >> x >> y >> z;
        out[x].push_back(std::make_pair(y, z));
    }
    dp[1].insert(0);
    for (int i = 1; i < n; ++i) {
        for(auto u : out[i]) {
            for (auto v : dp[i]) {
                dp[u.first].insert(v + u.second);
            }
        }
    }
    for (int i = 1; i <= q; ++i) {
        std::cin >> x >> y;
        auto t = dp[x].lower_bound(y);
        std::cout << (t != dp[x].end() && *t * (p - 1) <= p * y);
    }
    std::cout << std::endl;
    return 0;
}