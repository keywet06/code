#include <bits/stdc++.h>

using int64 = long long;

const int N = 100005;

int n, x;
int a[N];

int64 ans;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n, ++n;
    for (int i = 1; i < n; ++i) std::cin >> a[i];
    for (int i = 1; i < n; ++i) std::cin >> x, a[i] -= x;
    for (int i = 1; i <= n; ++i) ans += a[i] > a[i - 1] ? a[i] - a[i - 1] : 0;
    std::cout << ans << std::endl;
    return 0;
}