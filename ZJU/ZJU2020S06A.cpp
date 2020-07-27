#include <bits/stdc++.h>
const int N = 2000;
int n, m, k, r, l, ans, p, c, s;
int a[N][N];
inline void fill(int x, int y, int c) {
    for (int i = 0; i < y; ++i) {
        for (int j = 0; j < y; ++j) {
            a[x + i][x + j] = c;
        }
    }
}
int main() {
    srand(time(NULL));
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m;
    s = n - m;
    if (s < n) {
        while (p < n) {
            fill(p, n - p, c);
            s = c ? m : n - p - m;
            if (s <= 0) break;
            k = (n - p) / s;
            r = (n - p) % s;
            if (r) {
                for (int i = 0; i < k - 1; ++i) fill(p + i * s, s, !c);
                p += s * (k - 1);
                if (!c) m -= s * (k - 1);
            } else {
                for (int i = 0; i < k; ++i) fill(p + i * s, s, !c);
                p += s * k;
                if (!c) m -= s * k;
            }
            c ^= 1;
        }
    }
    l = 0;
    r = n * n + 1;
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) ans += a[i][j];
    std::cout << ans << '\n';
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << (a[i][j] ? --r : ++l) << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}