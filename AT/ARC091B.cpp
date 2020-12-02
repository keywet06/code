#include <bits/stdc++.h>

typedef long long int64;

int n, k;

int64 ans;

int main() {
    std::cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        if (i <= k) continue;
        ans += i - k;
        if (k == 0) --ans;
        int t = n / i - 1;
        ans += t * (i - k), t = n / i * i + k;
        if (t <= n) ans += n - t + 1;
    }
    std::cout << ans << std::endl;
    return 0;
}