#include <bits/stdc++.h>

namespace oct {

template <typename _Tp>
inline _Tp &mid(_Tp &x, _Tp y) {
    return x = std::min(x, y);
}
template <typename _Tp>
inline _Tp &mad(_Tp &x, _Tp y) {
    return x = std::max(x, y);
}

} // namespace oct

const int D[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int m, d, ans = 9;
std::string s;

int main() {
    std::cin >> s;
    m = (s[0] - '0') * 10 + (s[1] - '0');
    d = (s[3] - '0') * 10 + (s[4] - '0');
    for (int i = 1; i <= 12; ++i) {
        oct::mid(ans, (m / 10 != i / 10) + (m % 10 != i % 10) + (d > D[i]));
    }
    std::cout << ans + !d << std::endl;
    return 0;
}