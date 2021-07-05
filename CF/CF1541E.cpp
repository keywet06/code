#include <bits/stdc++.h>

using int64 = long long;

const int P = 1000000007;
const int N = 105;
const int M = N * N;

int n, q, x, p, w;

int64 t;
int64 f[M];

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    f[0] = 1;
    for (int i = 1; i <= n; ++i) {
        std::cin >> x;
        t = 0;
        for (int j = M - 1; j; --j) {
            if (j - x >= 0) t += f[j - x];
            t -= f[j], f[j] = (f[j] + t) % P;
        }
    }
    for (int i = 0; i <= 10; ++i) std::cerr << f[i] << ' ';
    std::cerr << std::endl;
    for (int i = 1; i < n; ++i) std::cin >> x, p += w += x;
    for (int i = M - 2; ~i; --i) f[i] = (f[i] + f[i + 1]) % P;
    std::cin >> q;
    while (q--) {
        std::cin >> x;
        std::cout << f[std::min(std::max(x * n + p, 0), M - 1)] << '\n';
    }
    return 0;
}