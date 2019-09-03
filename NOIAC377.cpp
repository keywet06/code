#include "kw/BigInt.hpp"
int m, n;
kw::BigInt a = 1;
int main() {
    scanf("%d %d", &n, &m);
    if (n > m) {
        std::swap(n, m);
    }
    for (int i = 1; i <= n; ++i) {
        a *= m - n + i;
        a /= i;
    }
    if (a.length() > 50) {
        a.makelen(50);
        a.zero();
    }
    std::cout << a << std::endl;
    return 0;
}