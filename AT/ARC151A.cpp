#include <bits/stdc++.h>

int n;

std::string s, t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> s >> t;
    int f = 0, g = 0, d = 0, e = 0;
    for (int i = 0; i < n; ++i) d += s[i] == '0' && t[i] == '1', e += s[i] == '1' && t[i] == '0';
    if ((d + e) & 1) return std::cout << -1 << '\n', 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == t[i]) {
            std::cout << 0;
        } else {
            if ((f == d + e >> 1 || s[i] == '0') && g < d + e >> 1) {
                std::cout << s[i], ++g;
            } else {
                std::cout << t[i], ++f;
            }
        }
    }
    std::cout << '\n';
    return 0;
}