#include <bits/stdc++.h>

using ldouble = long double;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    ldouble x, ux1 = 0, ux2 = 0, Ans = 0;
    while (n--) {
        std::cin >> x;
        Ans += (3 * ux2 + 3 * ux1 + 1) * x;
        ux2 = (ux2 + 2 * ux1 + 1) * x, ux1 = (ux1 + 1) * x;
    }
    std::cout << std::fixed << std::setprecision(1);
    std::cout << Ans << std::endl;
    return 0;
}