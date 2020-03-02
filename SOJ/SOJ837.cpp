#include <bits/stdc++.h>
const int N = 41;
int n;
int a[N], b[N];
int c[N][N * N];
int main() {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 1; i < 1 << n; ++i) {
        int s = 0, b = 0;
        for (int j = 1; j <= n; ++j) {
            if (i & (1 << (j - 1))) {
                ++b;
                for (int k = 1; k < j; ++k) {
                    if (i & (1 << (k - 1)) && a[k] > a[j]) {
                        ++s;
                    }
                }
            }
        }
        ++c[b][s];
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= n * n; ++j) {
            if (c[i][j]) {
                std::cout << j << " " << c[i][j] << std::endl;
                break;
            }
        }
    }
    return 0;
}