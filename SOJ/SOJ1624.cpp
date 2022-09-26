#include <bits/stdc++.h>

const int N = 2005;

int T;
int f[N][N];

std::string s, t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int T;
    std::cin >> T;
    while (T--) {
        std::cin >> s >> t;
        int n = s.length(), m = t.length();
        s = ' ' + s + ' ', t = ' ' + t + ' ';
        memset(f, 0, sizeof(f)), f[0][0] = 1;
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                if (!f[i][j]) continue;
                if (s[i + 1] == t[j + 1] || t[j + 1] == '.') f[i + 1][j + 1] = 1;
                if (s[i] == s[i + 1] && t[j] == '*') f[i + 1][j] = 1;
                if (t[j + 1] == '*') f[i][j + 1] = 1;
            }
        }
        int Ans = 0;
        for (int i = 1; i <= n; ++i) Ans += f[i][m];
        std::cout << Ans << '\n';
    }
    return 0;
}