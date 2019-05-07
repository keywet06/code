#include "BigInt.hpp"
int n, x;
kw::BigInt a, b;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        a = 0;
        for (int j = 1; j < 9; ++j) {
            scanf("%d", &x);
            a += (kw::BigInt(2) ^ x);
        }
        std::cin >> b;
        a += b;
        std::cout << a << std::endl;
    }
    return 0;
}