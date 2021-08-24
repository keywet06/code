#include <bits/stdc++.h>

using int64 = long long;

namespace oct {

inline void ios(bool enable = false, std::string s = "") {
    if (enable) {
        std::string t;
        freopen((t = s + ".in").data(), "r", stdin);
        freopen((t = s + ".out").data(), "w", stdout);
    }
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
}

}  // namespace oct

const int N = 600005;

int n, q, l, S, T, now;
int len[N];

std::string s[N];

std::vector<int> fail[N];

int main() {
    oct::ios(true, "string");
    std::cin >> n >> q;
    for (int i = 1; i <= n; ++i) std::cin >> s[i], len[i] = s[i].length();
    for (int i = 1; i <= n; ++i) {
        s[i] = ' ' + s[i], now = 0;
        fail[i].resize(len[i] + 1);
        for (int j = 2; j <= len[i]; ++j) {
            while (now && s[i][j] != s[i][now + 1]) now = fail[i][now];
            fail[i][j] = now += s[i][j] == s[i][now + 1];
        }
    }
    while (q--) {
        std::cin >> S >> T;
        now = 0;
        for (int i = std::max(1, len[T] - len[S]); i <= len[S]; ++i) {
            while (now && s[S][i] != s[T][now + 1]) now = fail[i][now];
            now += s[S][i] == s[T][now + 1];
        }
        std::cout << now << std::endl;
    }
    return 0;
}