#include <bits/stdc++.h>
const int B = 2;
const int N = 200000;
const int Np = N + 5;
int cnt, n, m, p, l, r, o, x, ans;
int v[Np];
std::multiset<int> set;
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m >> p;
    for (int i = 1; i <= n; ++i) {
        std::cin >> v[i];
        set.insert(v[i]);
    }
    for (int i = 1; i <= m; ++i) {
        std::cin >> o;
        if (o == 1) {
            std::cin >> x;
            x ^= ans * p;
            set.insert(x);
        } else if (o == 2) {
            std::cin >> x;
            x ^= ans * p;
            set.erase(set.find(x));
        } else {
            std::cin >> l >> r;
            l ^= ans * p;
            r ^= ans * p;
            ans = 0;
            auto it = set.upper_bound(r);
            if (it == set.begin()) {
                std::cout << (ans = 0) << std::endl;
                continue;
            }
            --it;
            int a = 0;
            while (1) {
                v[++a] = *it;
                if (it == set.begin() || a > 35 || *--it < l) {
                    break;
                }
            }
            for (int i = 1; i < a; ++i) {
                for (int j = i + 1; j <= a; ++j) {
                    ans = std::max(ans, v[i] & v[j]);
                }
            }
            std::cout << ans << std::endl;
        }
    }
    return 0;
}