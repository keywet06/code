#include <bits/stdc++.h>
const int N = 200000;
const int S = 500;
int n, s, opt, l, r, c;
int a[N];
int size[S];
int f[S][S * 2];
inline void rebuild() {
    s = 0;
    for (int i = 0; i < S; ++i) {
        for (int j = 0; j < size[i]; ++j) a[s++] = f[i][j];
        size[i] = 0;
    }
    for (int i = 0; i < s; ++i) {
        f[i / S][i % S] = a[i];
        ++size[i / S];
    }
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n;
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    for (int i = 0; i < n; ++i) {
        f[i / S][i % S] = a[i];
        ++size[i / S];
    }
    while (n--) {
        std::cin >> opt >> l >> r >> c;
        if (opt == 0) {
            for (int i = 0; i < S; ++i) {
                if (l > size[i]) {
                    l -= size[i];
                    continue;
                }
                for (int j = size[i]; j >= l; --j) {
                    f[i][j] = f[i][j - 1];
                }
                f[i][l - 1] = r;
                ++size[i];
                if (size[i] == S * 2) rebuild();
                break;
            }
        } else {
            for (int i = 0; i < S; ++i) {
                if (r > size[i]) {
                    r -= size[i];
                    continue;
                }
                std::cout << f[i][r - 1] << '\n';
                break;
            }
        }
    }
    return 0;
}