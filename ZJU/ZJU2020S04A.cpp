#include <bits/stdc++.h>
const int N = 1000005;
int n, ans, max, x, c;
int a[N];
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        max = std::max(max, a[i]);
    }
    ans = max;
    c = max + 1 >> 1;
    for (int i = 1; i <= n; ++i) {
        while (a[i] < c) {
            a[i] <<= 1;
            ++ans;
        }
        if (a[i] < max) ++ans;
    }
    std::cout << ans << std::endl;
    return 0;
}