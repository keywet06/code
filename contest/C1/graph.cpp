#include <bits/stdc++.h>

namespace oct {

inline void ios(bool enable = false, std::string s = "") {
    if (enable) {
        std::string t;
        freopen((t = s + ".in").data(), "r", stdin);
        freopen((t = s + ".out").data(), "w", stdout);
    }
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
}

template <typename _Tp>
inline _Tp gcd(_Tp x, _Tp y) {
    return y ? gcd(y, x % y) : x;
}

}  // namespace oct

using int64 = long long;

int T, n, m;

int64 s, x;

int main() {
    oct::ios(true, "graph");
    std::cin >> T;
    while (T--) {
        std::cin >> n >> m >> s;
        for (int i = 1; i < m; ++i) std::cin >> x, s = oct::gcd(x, s);
        std::cout << s << '\n';
    }
    return 0;
}