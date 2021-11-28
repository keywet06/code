#include <bits/stdc++.h>

using int64 = long long;

const int N = 805;
const int K = 85;
const int64 Z = 1000000000000000;

int n, k;

int64 a[N], b[N];
int64 f[K][N];

long double x;

template<typename _Tp>
_Tp &mad(_Tp &x, _Tp y) { return x > y ? x : (x = y); }

int main() {
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> k;
    for (int i = 1; i <= n; ++i) std::cin >> x, a[i] = int64(x * Z) + a[i - 1];
    for (int i = 1; i <= n; ++i) std::cin >> x, b[i] = int64(x * Z) + b[i - 1];
    memset(f, 1, sizeof(f));
    f[0][0] = 0;
    for (int i = 1; i <= k; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int l = 0; l < j; ++l) {
                mad(f[i][j], f[i - 1][l] + std::abs(a[j] - a[l] - b[j] + b[l]));
            }
        }
    }
    std::cout << std::fixed << std::setprecision(6);
    std::cout << (long double)(f[k][n]) / Z << std::endl;
    return 0;
}