#include <bits/stdc++.h>
const int N = 10;
const int mod = 998244353;
char s[N];
int t, x, y, n;
long long ans;
int main() {
    register int a, b, i;
    std::cin >> n;
    for (i = 1; i <= n; ++i) {
        t = i;
        x = y = 0;
        while (t) {
            x = x * 10 + t % 10;
            t /= 10;
            ++y;
        }
        sprintf(s, "%d", i);
        t = y;
        y = 0;
        for (a = 0; a < t; ++a) {
            for (b = a + 1; b < t; ++b) {
                y += s[a] > s[b];
            }
        }
        ans += std::abs(x - y);
    }
    std::cout << ans % mod << std::endl;
    return 0;
}