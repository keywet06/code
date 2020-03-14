#include <bits/stdc++.h>
const int N = 1005;
int n, max;
int a[N];
int g[N][N];
long long ans;
int main() {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 1; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            g[i][j] = std::__gcd(a[i], a[j]);
        }
    }
    for (int l = 1; l <= n; ++l) {
        for (int r = l; r <= std::min(l + n - 3, n); ++r) {
            max = 0;
            for (int i = 1; i <= n; ++i) {
                if (l <= i && i <= r) {
                    continue;
                }
                for (int j = i + 1; j <= n; ++j) {
                    if (l <= j && j <= r) {
                        continue;
                    }
                    max = std::max(max, g[i][j]);
                }
            }
            ans += max;
        }
    }
    std::cout << ans << std::endl;
    return 0;
}