#include <bits/stdc++.h>

const int N = 105;

int n, k, ans, flag;
int a[N], f[N];

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> a[i], f[i] = f[i - 1] + a[i];
    for (int l = 1; l <= n; ++l) {
        for (int r = l; r <= n; ++r) {
            if ((k = f[r] - f[l - 1]) % (r - l + 1)) continue;
            k /= r - l + 1, flag = 0;
            for (int i = l; i <= r; ++i) flag |= a[i] == k;
            ans += flag;
        }
    }
    std::cout << ans << std::endl;
    return 0;
}