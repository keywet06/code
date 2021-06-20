#include <bits/stdc++.h>

const int N = 1500005;
const int K = 20;

int n, k, c, d;
int a[N];
int st[K][N];

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> k;
    memset(st, 127, sizeof(st));
    for (int i = 1; i <= n; ++i) std::cin >> a[i], st[0][i] = a[i];
    for (int i = 1; i < K; ++i) {
        for (int j = 1; j <= n; ++j) {
            st[i][j] = std::min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
        }
    }
    while ((1 << (c + 1)) <= k) ++c;
    d = k - (1 << c);
    for (int i = 1; i <= n - k; ++i) {
        std::cout << std::min(st[c][i + d], st[c][i]) << ' ';
    }
    std::cout << std::min(st[c][n - k + 1], st[c][n - k + 1 + d]) << '\n';
    memset(st, 128, sizeof(st));
    for (int i = 1; i <= n; ++i) st[0][i] = a[i];
    for (int i = 1; i < K; ++i) {
        for (int j = 1; j <= n; ++j) {
            st[i][j] = std::max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
        }
    }
    for (int i = 1; i <= n - k; ++i) {
        std::cout << std::max(st[c][i + d], st[c][i]) << ' ';
    }
    std::cout << std::max(st[c][n - k + 1], st[c][n - k + 1 + d]) << '\n';
    return 0;
}