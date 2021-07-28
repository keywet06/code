#include <algorithm>
#include <cstring>
#include <iostream>

#if __cplusplus >= 201103L
using int64 = long long;
#else
typedef long long int64;
#endif

const int N = 15;
const int N_ = 11;
const int X = 1 << N_;

int n, m;

int64 f1[X], f2[X];
int64 *f, *g;

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    while (std::cin >> n >> m, n) {
        f = f1, g = f2;
        memset(f, 0, sizeof(f1)), f[0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < m; ++j) {
                memset(g, 0, sizeof(f1));
                for (int x = 0; x < 1 << m; ++x) {
                    if (!f[x]) continue;
                    g[x ^ (1 << j)] += f[x];
                    if (j != m - 1 && !(x & (1 << j)) && !(x & (1 << j + 1))) {
                        g[x | (1 << j + 1)] += f[x];
                    }
                }
                std::swap(f, g);
            }
        }
        std::cout << f[0] << '\n';
    }
    return 0;
}
