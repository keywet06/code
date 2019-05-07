#include "BigInt.hpp"
int n;
kw::BigInt a, b, c;
int main() {
    scanf("%d", &n);
    if (!n) {
        printf("0");
        return 0;
    }
    b = 1;
    c = 1;
    for (int i = 1; i < n; ++i) {
        a = b;
        b = c;
        c = a + b;
    }
    std::cout << c;
    return 0;
}