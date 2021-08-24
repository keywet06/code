#include <bits/stdc++.h>

using int64 = long long;
using ldb = long double;

const ldb p = 0.04999999999999;
const ldb q = 10;

inline ldb &mid(ldb &x, ldb y) { return x = std::min(x, y); }

int main() {
    ldb a, b;
    int64 n;
    while (std::cin >> a >> b >> n) {
        if (a <= b) {
            std::cout << "0" << std::endl;
            continue;
        }
        mid(a = a + p, q), mid(b = b + p, q);
        std::cout << int64(ceil(ldb(b * n - int64(a * n)) / (1 - b))) << '\n';
    }
    return 0;
}
