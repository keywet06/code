#include <bits/stdc++.h>

using int64 = long long;
using int128 = __int128;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int64 n, k, d = 0;
    std::cin >> k >> n;
    if (k == 1 && n <= 1000) {
        while (k--) d = d * 10 + 9;
        for (int64 i = d;; i += d) {
            int64 t = i, m = 0;
            while (t) m = std::max(m, t % 10), t /= 10;
            if (!(n -= m < 9)) return std::cout << i / d << '\n', 0;
        }
    }
    
    return 0;
}