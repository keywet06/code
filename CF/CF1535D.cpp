#include <bits/stdc++.h>

const int N = 1000005;

int k, n, q, x, y, c;
int a[N];

std::string s, s1;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> k;
    std::cin >> s;
    for (int i = 0; i < 1 << k - 1; ++i) a[i] = 1;
    x = 1 << k - 1;
    for (int i = k - 2; i; --i) {
        for (int j = 0; j < 1 << i; ++j) {
            a[x + j] = s[x + j] == '?' ? s[y | j << 1] + s[y | j << 1 | 1]
                                       : s[y | j << 1 | s[x + j] - '0'];
        }
        x |= 1 << i, y |= 1 << i - 1;
    }
    std::cin >> q;
    while (q--) {
        std::cin >> x >> s1, c = k - 1, s[--x];
        while (1 << c | x) --c;
    }
    return 0;
}