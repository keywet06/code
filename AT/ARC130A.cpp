#include <bits/stdc++.h>

using int64 = long long;

char l;

int n;

int64 x, ans;

std::string s;

inline void add(char c) {
    if (c != l) ans += x * (x - 1) / 2, x = 0;
    ++x, l = c;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> s;
    for (char ch : s) add(ch);
    add(1);
    std::cout << ans << '\n';
    return 0;
}
