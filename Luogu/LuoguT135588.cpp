#include <bits/stdc++.h>
const int N = 4000005;
int c[N], s[N];
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    register int n, x, i, p, j;
    register long long ans;
    std::cin >> n;
    for (i = 1; i <= 2000; ++i) {
        for (j = (i - 1) * (i - 1) + 1; j <= i * i; ++j) {
            s[j] = i - 1;
        }
    }
    while (n--) {
        std::cin >> x;
        i = 1;
        p = s[x];
        while (i < p) {
            if (x % i == 0) ++c[i], ++c[x / i];
            ++i;
        }
        if (i * i == x) ++c[i];
    }
    ans = 0;
    for (int i = 1; i < N; ++i) {
        ans = std::max(ans, (long long)(c[i] > 1) * c[i] * i);
    }
    std::cout << ans << std::endl;
    return 0;
}