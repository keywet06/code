#include <bits/stdc++.h>

namespace oct {

void ios();

inline void ios() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
}

}  // namespace oct

int T, a, b, c, d, e, f;

int main() {
    oct::ios();
    std::cin >> T;
    while (T--) {
        std::cin >> a >> b >> c >> d >> e >> f;
        std::cout << (!c && d || !a && b && d || b * d * f > a * c * e
                          ? "MEI\n"
                          : "FON\n");
    }
    return 0;
}