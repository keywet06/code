#include <bits/stdc++.h>
long long i, sum, as, n, m, u, r;
void ans(const long long x);
inline void ans(const long long x) {
}
int main() {
    std::cin >> n;
    m = 0;
    for (int i = 1; i <= n; ++i) {
        if (i == 1 << (m + 1)) ++m;
        ans(i);
        u = 0;
        r = i;
        for (i = 0; i <= m; ++i) {
            u |= ((i >> i) & 1) << (m - i);
        }
        r += u;
        while (r) {
            ++sum;
            r ^= r & -r;
        }
    }
    std::cout << sum << std::endl;
    return 0;
}