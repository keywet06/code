#include <bits/stdc++.h>
const int N = 50000;
const int S = 225;
int n, opt, l, r, c;
long long a[N];
long long plus[S];
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n;
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    for (int i = 0; i < n; ++i) {
        std::cin >> opt >> l >> r >> c;
        --l, --r;
        if (opt == 0) {
            if (l / S == r / S) {
                for (int i = l; i <= r; ++i) a[i] += c;
                continue;
            }
            for (int i = l; i < l / S * S + S; ++i) a[i] += c;
            for (int i = r / S * S; i <= r; ++i) a[i] += c;
            for (int i = l / S + 1; i < r / S; ++i) plus[i] += c;
        } else {
            std::cout << plus[r / S] + a[r] << '\n';
        }
    }
    return 0;
}