#include "BigInt.hpp"
int m, n;
kw::BigInt a = 1;
int main() {
    scanf("%d %d", &n, &m);
    if (n > m) {
        std::swap(n, m);
    }
    for (int i = m - n + 1; i <= m; ++i) {
        a *= i;
    }
    for (int i = 1; i <= n; ++i) {
        a /= i;
    }
    std::cout << a << std::endl;
    return 0;
}