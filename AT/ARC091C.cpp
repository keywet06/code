#include <bits/stdc++.h>

const int N = 300005;

int n, a, b;
int cnt[N];

int main() {
    std::cin >> n >> a >> b;
    int d = (n - 1) / a + 1, u = n - a + 1;
    if (b > u || b < d) return std::cout << -1 << std::endl, 0;
    cnt[1] = a;
    int t = n - a;
    for (int i = 2; i <= b; ++i) t -= cnt[i] = t - a >= b - i ? a : t - (b - i);
    t = n;
    for (int i = b; i >= 1; --i) {
        for (int j = t - cnt[i] + 1; j <= t; ++j) std::cout << j << ' ';
        t -= cnt[i];
    }
    std::cout << std::endl;
    return 0;
}