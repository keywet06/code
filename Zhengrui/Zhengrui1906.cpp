#include <bits/stdc++.h>

using int64 = long long;

int64 a, b, c, ans;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> a >> b;
    if (a == b) {
        c = 1;
        while (a >= (c * c + c) / 2) {
            a -= (c * c + c) / 2, ans += c + 1, ++c;
        }
        ans += a / c * 2, a %= c;
        ans += a >= c / 2 + (c & 1);
        return std::cout << ans << '\n', 0;
    }
    return 0;
}