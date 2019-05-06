#include "BigInt.hpp"
kw::BigInt a, b, c;
int main() {
    std::cin >> a >> b;
    if (a < b) {
        printf("-");
        c = b - a;
    } else {
        c = a - b;
    }
    std::cout << c;
    return 0;
}