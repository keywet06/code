#include <bits/stdc++.h>

using int64 = long long;

int main() {
    int h, w, k;
    std::cin >> h >> w >> k;
    int Sum = 0;
    int64 SumA = 0, SumB = 0;
    for (int i = 0, x; i < h; ++i) {
        std::cin >> x;
        Sum = (Sum + x) % k;
        SumA += (int64(k - 1) * w + k - x) % k;
    }
    for (int i = 0, x; i < w; ++i) {
        std::cin >> x;
        Sum = (Sum + k - x) % k;
        SumB += (int64(k - 1) * h + k - x) % k;
    }
    if (Sum != 0) return std::cout << -1 << std::endl, 0;
    std::cout << int64(k - 1) * h * w - std::max(SumA, SumB) << std::endl;
    return 0;
}