#include <bits/stdc++.h>
int T, l, r;
inline long long S(long long x) {
    if (x == 0) return 0;
    long long ans = 0, c = sqrt(x + 0.0001), i;
    for (i = 1; i <= c; ++i) ans += (x / i) * (x / i);
    for (i = 1; i < x / c; ++i) ans += i * i * (x / i - x / (i + 1));
    for (i = 1; i <= c; ++i) ans -= x / i;
    for (i = 1; i < x / c; ++i) ans -= i * (x / i - x / (i + 1));
    return ans / 2;
}
int main() {
    std::cin >> T;
    while (T--) {
        std::cin >> l >> r;
        std::cout << S(r) - S(l - 1) << std::endl;
    }
    return 0;
}