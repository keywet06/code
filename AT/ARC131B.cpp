#include <bits/stdc++.h>

const int N = 705;

int n, m;
int num[N];
int a[N][N];

std::string s;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        std::cin >> s;
        for (int j = 0; j < m; ++j) {
            if (s[j] != '.') a[i][j + 1] = s[j] - '0';
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i][j]) continue;
            num[1] = num[2] = num[3] = num[4] = num[5] = 0;
            ++num[a[i - 1][j]], ++num[a[i + 1][j]];
            ++num[a[i][j - 1]], ++num[a[i][j + 1]];
            if (!num[1] && (a[i][j] = 1)) continue;
            if (!num[2] && (a[i][j] = 2)) continue;
            if (!num[3] && (a[i][j] = 3)) continue;
            if (!num[4] && (a[i][j] = 4)) continue;
            if (!num[5] && (a[i][j] = 5)) continue;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) std::cout << a[i][j];
        std::cout << '\n';
    }
    return 0;
}
