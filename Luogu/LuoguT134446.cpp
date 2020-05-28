#include <bits/stdc++.h>
const int N = 300005;
int n, ans, max, tag;
int a[N], t[N];
int main() {
    register int i, j, k;
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n;
    for (i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }
    for (i = 1; i <= n; ++i) {
        t[a[i]] = 1;
        ans += a[i] == 1;
        max = a[i];
        tag = 1;
        for (j = i + 1; j <= n; ++j) {
            if (t[a[j]] == 1) {
                tag = 0;
                for (k = i; k <= j; ++k) {
                    t[a[k]] = 0;
                }
                break;
            }
            t[a[j]] = 1;
            max = std::max(max, a[j]);
            if (j - i + 1 == max) {
                ++ans;
            }
        }
    }
    std::cout << ans << std::endl;
    return 0;
}