#include <bits/stdc++.h>

const int N = 2000005;

int n, cnt;
int l[N], r[N], p[N];

long long ans;

std::string s;

inline void connect(int x, int y) {
    ++cnt, l[cnt] = x, r[cnt] = y;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> s, n = s.length();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; i - j >= 0 && i + j < n; ++j) {
            if (s[i - j] != s[i + j]) break;
            connect(i - j, i + j);
        }
        for (int j = 1; i - j >= 0 && i + j - 1 < n; ++j) {
            if (s[i - j] != s[i + j - 1]) break;
            connect(i - j, i + j - 1);
        }
    }
    for (int i = 1; i <= cnt; ++i) ++p[r[i]];
    for (int i = 1; i < n; ++i) p[i] += p[i - 1];
    for (int i = 1; i <= cnt; ++i) ans += p[l[i] - 1];
    std::cout << ans << std::endl;
    return 0;
}