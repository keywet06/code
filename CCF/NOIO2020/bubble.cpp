#include <bits/stdc++.h>
const int N = 200005;
int n, m, x, y, t;
int p[N], o[N], s[N];
int main() {
    freopen("bubble.in", "r", stdin);
    freopen("bubble.out", "w", stdout);
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        std::cin >> p[i];
    }
    for (int i = 1; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            s[0] += p[i] > p[j];
        }
    }
    for (int i = 1; i < n; ++i) {
        s[i] = s[i - 1];
        for (int j = 1; j < n; ++j) {
            if (p[j] > p[j + 1]) {
                std::swap(p[j], p[j + 1]);
                --s[i];
            }
        }
    }
    for (int i = 1; i <= m; ++i) {
        std::cin >> x >> y;
        if (x == 1) {
            x = std::max(p[y], p[y + 1]);
            t = 0;
            for (int j = y + 2; j <= n; ++j) {
                if (p[j] > x) {
                    ++t;
                }
            }
            x = p[y] > p[y + 1] ? -1 : 1;
            for (int j = 0; j <= t; ++j) {
                s[j] += x;
            }
            std::swap(p[y], p[y + 1]);
        } else {
            std::cout << s[y] << std::endl;
        }
    }
    return 0;
}