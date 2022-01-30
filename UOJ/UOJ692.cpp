#include <bits/stdc++.h>

using int64 = long long;

const int N = 72;
const int D = 37;
const int M = 30005;
const int P = 998244353;

template <typename Type1, typename Type2>
inline void Add(Type1 y, Type2 &x) {
    if ((x += y) >= P) x -= P;
}

template <typename Type1, typename Type2>
inline void Del(Type1 y, Type2 &x) {
    if ((x -= y) < 0) x += P;
}

int n, V, si;
int a[N], s[N];
int f[N][D][M], g[N][D][M];

int64 Ans, S;

inline int Sum(int l, int r) { return l > 0 ? s[r] - s[l - 1] : s[r]; }

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> V;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    std::sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + a[i];
    f[0][0][0] = 1, g[n + 1][0][0] = 1;
    for (int i = 0, d; d = a[i + 1], i < n; ++i) {
        for (int j = 0, Ej = std::min(i, n - i - 1); j <= Ej; ++j) {
            for (int k = 0, Ek = Sum(i - j + 1, i); k <= Ek; ++k) {
                Add(f[i][j][k], f[i + 1][j][k]);
                Add(f[i][j][k], f[i + 1][j + 1][k + d]);
            }
        }
    }
    for (int i = n + 1, d; d = a[i - 1], i > 1; --i) {
        for (int j = 0, Ej = std::min(n - i + 1, i - 2); j <= Ej; ++j) {
            for (int k = 0, Ek = Sum(n - j + 1, n); k <= Ek; ++k) {
                Add(g[i][j][k], g[i - 1][j][k]);
                Add(g[i][j][k], g[i - 1][j + 1][k + d]);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 0, Ej = std::min(i - 1, n - i); j <= Ej; ++j) {
            S = 0, si = 2 * j * a[i];
            for (int k = std::min(Sum(n - j + 1, n), si); k >= 0; --k) {
                Add(g[i + 1][j][k], S);
            }
            for (int k = 0, Ek = Sum(i - j, i - 1); k <= Ek; ++k) {
                Del(g[i + 1][j][si - k], S);
                Ans += S * f[i - 1][j][k] % P;
            }
        }
    }
    std::cout << Ans % P << std::endl;
    return 0;
}