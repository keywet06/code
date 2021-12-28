#include <bits/stdc++.h>

using int64 = long long;

const int N = 200005;
const int M = 5005;
const int D = M << 1;

int n, m, x;

int64 Sum;
int64 a[M], b[M];
int64 Ans[D];

int main() {
    std::ios::sync_with_stdio(0);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        std::cin >> x, ++a[x];
        std::cin >> x, ++b[x];
    }
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= m; ++j) Ans[i + j] += a[i] * a[j];
    }
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= m; ++j) Ans[i + j + 1] -= b[i] * b[j];
    }
    for (int i = 0; i <= m * 2; ++i) std::cout << (Sum += Ans[i]) << '\n';
    return 0;
}