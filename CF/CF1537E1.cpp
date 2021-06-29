#include <bits/stdc++.h>

int n, k, p;

std::string s;

int main() {
    std::cin >> n >> k;
    std::cin >> s;
    p = n;
    for (int i = 1; i < n; ++i) {
        if (s[i] > s[0]) {
            p = i;
            break;
        }
    }
    for (int i = 0; i < k; ++i) std::cout << s[i % p];
    std::cout << std::endl;
    return 0;
}