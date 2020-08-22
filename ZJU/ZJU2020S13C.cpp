#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
int main() {
    register int n, c, a, ans = 0;
    std::cin >> n;
    for (c = 1; c <= n; ++c) {
        for (a = c * 2; a <= n; a += c) {
            ans += a ^ (a - c) == c;
        }
    }
    std::cout << ans * 2 << std::endl;
    return 0;
}