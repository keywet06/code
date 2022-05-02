#include <bits/stdc++.h>

using int64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int T;
    std::cin >> T;
    while (T--) {
        int64 n;
        std::cin >> n;
        if (n % 3 == 0) {
            std::cout << 1 << ' ' << n << '\n';
        } else {
            std::array<std::vector<int64>, 2> Cnt;
            int o = 0;
            int64 c = 1, t = n;
            while (t) {
                if (t & 1) Cnt[o].push_back(c);
                t >>= 1, c <<= 1, o ^= 1;
            }
            if (n % 3 == 2) Cnt[0].swap(Cnt[1]);
            int c1 = Cnt[0].size(), c2 = Cnt[1].size();
            std::vector<int64> &v1 = Cnt[0], &v2 = Cnt[1];
            if (c1 >= 2) {
                std::cout << 2 << ' ' << (n ^ v1[0]) << ' ' << (n ^ v1[1]) << '\n';
            } else if (c2 >= 4) {
                std::cout << 2 << ' ' << (n ^ v2[0] ^ v2[1]) << ' ' << (n ^ v2[2] ^ v2[3]) << '\n';
            } else if (c1 >= 1 && c2 >= 2) {
                std::cout << 2 << ' ' << (n ^ v1[0]) << ' ' << (n ^ v2[0] ^ v2[1]) << '\n';
            } else {
                std::cout << -1 << '\n';
            }
        }
    }
    return 0;
}