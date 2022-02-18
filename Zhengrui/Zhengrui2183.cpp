#include <bits/stdc++.h>

using int64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int n, k;
    std::cin >> n >> k, --k;
    std::vector<int64> a(n), b;
    int64 Ans = 0;
    for (int i = 0; i < n; ++i) std::cin >> a[i], Ans += a[i];
    for (int i = 0; i < n; ++i) {
        int Sum = 0;
        for (int j = i; j < n - !i; ++j) b.push_back(Sum += a[j]);
    }
    std::sort(b.begin(), b.end(), [](int x, int y) { return x > y; });
    for (int i = 0; i < k; ++i) Ans += b[i];
    std::cout << Ans << std::endl;
    return 0;
}