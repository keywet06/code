#include <bits/stdc++.h>
const int N = 50000;
const int S = 225;
int n, opt, l, r;
long long ans, c;
long long a[N];
long long plus[S], sum[S];
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n;
    for (int i = 0; i < n; ++i) std::cin >> a[i], sum[i / S] += a[i];
    for (int i = 0; i < n; ++i) {
        std::cin >> opt >> l >> r >> c;
        --l, --r;
        if (opt == 0) {
            if (l / S == r / S) {
                for (int i = l; i <= r; ++i) a[i] += c;
                sum[l / S] += (r - l + 1) * c;
                continue;
            }
            for (int i = l; i < l / S * S + S; ++i) a[i] += c;
            sum[l / S] += (l / S * S + S - l) * c;
            for (int i = r / S * S; i <= r; ++i) a[i] += c;
            sum[r / S] += (r - r / S * S + 1) * c;
            for (int i = l / S + 1; i < r / S; ++i) plus[i] += c;
        } else {
            ans = 0;
            if (l / S == r / S) {
                for (int i = l; i <= r; ++i) ans += a[i] + plus[l / S];
                std::cout << ans % (c + 1) << '\n';
                continue;
            }
            for (int i = l; i < l / S * S + S; ++i) ans += a[i] + plus[l / S];
            for (int i = r / S * S; i <= r; ++i) ans += a[i] + plus[r / S];
            for (int i = l / S + 1; i < r / S; ++i) ans += plus[i] * S + sum[i];
            std::cout << ans % (c + 1) << '\n';
        }
    }
    return 0;
}