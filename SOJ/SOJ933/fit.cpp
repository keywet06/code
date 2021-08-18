#include <bits/stdc++.h>

long long T, n, f;

std::string s, x, m;

int main() {
    T = 10;
    while (T--) {
        std::getline(std::cin, s), f = 1;
        for (int i = 0; i < s.length(); ++i) {
            if (f) {
                if (s[i] == ':') f = 0, ++i;
                continue;
            }
            if (s[i] == ' ') {
                if (m == x) {
                    ++n;
                } else {
                    if (x != "") std::cout << x << ' ' << n << std::endl;
                    n = 1, x = m;
                }
                m = "";
                continue;
            }
            m = m + s[i];
        }
        if (m == x) {
            ++n;
        } else {
            if (x != "") std::cout << x << ' ' << n << std::endl;
            n = 1, x = m;
        }
        std::cout << x << ' ' << n << std::endl;
        n = 0, x = m = "";
        std::cout << std::endl;
    }
    return 0;
}