#include <bits/stdc++.h>

__int128_t n;

std::string s;

int main() {
    std::cin >> s;
    for (int i = 0; i < s.length(); ++i) {
        n = n * 10 + s[i] - '0';
    }
    n = (n + 5) / 6;
    s = "";
    while (n) s = char(n % 10 + '0') + s, n /= 10;
    std::cout << s << std::endl;
    return 0;
}