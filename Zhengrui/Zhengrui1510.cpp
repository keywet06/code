#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
int main() {
    register int a0, a1, a2, a3, a4, a5, b0, b1, b2, b3, b4, b5;
    register long long ans;
    std::cin >> b0 >> b1 >> b2 >> b3 >> b4 >> b5;
    for (a0 = 0; a0 <= b0; ++a0) {
        for (a1 = 0; a1 <= b1; ++a1) {
            for (a2 = 0; a2 <= b2; ++a2) {
                for (a3 = 0; a3 <= b3; ++a3) {
                    for (a4 = 0; a4 <= b4; ++a4) {
                        for (a5 = 0; a5 <= b5; ++a5) {
                            ans += std::max(std::abs(a0 - a3),
                                            std::max(std::abs(a1 - a4),
                                                     std::abs(a2 - a5))) ^
                                   a0 ^ a1 ^ a2 ^ a3 ^ a4 ^ a5;
                        }
                    }
                }
            }
        }
    }
    std::cout << ans << std::endl;
    return 0;
}