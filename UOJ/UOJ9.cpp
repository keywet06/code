#include <bits/stdc++.h>

const int N = 100005;

int n, Len;
int p[N];

std::string s[N], Num[N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n;
    for (int i = 1, x; i <= n; ++i) {
        std::cin >> s[i], p[i] = i, x = -1;
        for (char Ch : s[i]) {
            if (++x, Ch >= '0' && Ch <= '9') break;
        }
        Len = std::max(Len, int((Num[i] = s[i].substr(x, s[i].size() - x - 3)).size()));
    }
    for (int i = 1; i <= n; ++i) {
        if (Num[i].size() == Len) continue;
        int c = Num[i].size();
        Num[i].resize(Len);
        for (int j = c - 1; j >= 0; --j) Num[i][j + Len - c] = Num[i][j];
        for (int j = 0; j < Len - c; ++j) Num[i][j] = '0';
    }
    std::sort(p + 1, p + n + 1, [](int x, int y) { return Num[x] < Num[y]; });
    for (int i = 1; i <= n; ++i) std::cout << s[p[i]] << '\n';
    return 0;
}