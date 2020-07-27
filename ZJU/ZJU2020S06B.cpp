#include <bits/stdc++.h>
int n, m;
int main() {
    std::cin >> n >> m;
    n = n - m + (m + 1) / 2 - 1;
    m = (m + 1) / 2 - 1;
    if (~n & m) {
        std::cout << 0 << std::endl;
    } else {
        std::cout << 1 << std::endl;
    }
    return 0;
}