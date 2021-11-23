#include <bits/stdc++.h>

using int64 = long long;

const int P = 998244353;

int n, l, u;

int64 ans;

std::string s;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> s, n = s.length();
    int d = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'B') continue;
        if (!u && (u = s[l = i])) continue;
        if (u == s[i] && (l = i)) continue;
        u = s[i], ans += (l + 1ll) * (n - i) % P, l = i;
    }
    std::cout << ans % P << std::endl;
    return 0;
}