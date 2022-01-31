#include <bits/stdc++.h>

using int64 = long long;
using ldou = double;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cout << std::fixed << std::setprecision(2);
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    std::sort(a.begin(), a.end());
    int64 Sum = m, Num = 1;
    for (int i = 1; i < n; ++i) Sum += Sum > a[i] * Num++ ? 0 : m;
    int64 MaxAns = Sum * 1000 / Num;
    MaxAns = MaxAns / 10 + (MaxAns % 10 >= 5);
    std::cout << MaxAns / 100 << '.' << MaxAns / 10 % 10 << MaxAns % 10 << ' ';
    std::reverse(a.begin(), a.end());
    Sum = m, Num = 1;
    for (int i = 1; i < n; ++i) Sum += Sum > a[i] * Num++ ? 0 : m;
    int64 MinAns = Sum * 1000 / Num;
    MinAns = MinAns / 10 + (MinAns % 10 >= 5);
    std::cout << MinAns / 100 << '.' << MinAns / 10 % 10 << MinAns % 10 << '\n';
    return 0;
}