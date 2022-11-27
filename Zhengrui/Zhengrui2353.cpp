#include <bits/stdc++.h>

using int64 = long long;

const int N = 1000005;

int n;
int a[N];

int64 Ans;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n;
    for (int i = 1, l, r; i <= n; ++i) std::cin >> l >> r, a[i] = l + r, Ans += r - l;
    std::sort(a + 1, a + n + 1);
    for (int i = 1, j = n; i < j; ++i, --j) Ans += a[j] - a[i];
    std::cout << (Ans >> 1) << std::endl;
    return 0;
}