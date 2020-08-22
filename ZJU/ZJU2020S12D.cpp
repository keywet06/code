#include <bits/stdc++.h>
int T, x, y, z;
int main() {
    std::cin >> T;
    while (T--) {
        std::cin >> x >> y >> z;
        std::cout << (y == z ? '>' : '<') << std::endl;
    }
    return 0;
}