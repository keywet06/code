#include <bits/stdc++.h>

const int N = 200005;

int T, n, k, r, q, p;
int f[N], d[N];

inline int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }
inline int g(int x) { return x == f[x] ? x : f[x] = g(f[x]); }
inline void merge(int x, int y) { f[g(y)] = g(x); }

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> T;
    while (T--) {
        std::cin >> n >> k;
        for (int i = 1; i <= k; ++i) std::cin >> d[i];
        for (int i = 1; i <= n; ++i) f[i] = i;
        r = n;
        while (k) {
            if (d[k] * 2 < r) break;
            r = gcd(r, (r - d[k] % r + n % r) % r);
            --k;
        }
        for (int i = 1; i <= n - r; ++i) merge(i, i + r);
        for (int i = 1; i <= k; ++i) {
            for (int j = 1; j <= d[i]; ++j) merge(j, n - d[i] + j);
        }
        r = g(n), q = 0;
        for (int i = 1; i <= n; ++i) {
            if (g(i) != r) {
                q = i;
                break;
            }
        }
        if (!q) {
            for (int i = 1; i <= n; ++i) std::cout << 'a';
        } else if (q == 1) {
            for (int i = 1; i <= n; ++i) std::cout << (g(i) == r ? 'b' : 'a');
        } else {
            for (int i = n; i; --i) {
                if (g(i) != r) {
                    r = g(i);
                    break;
                }
            }
            for (int i = 1; i <= n; ++i) std::cout << (g(i) == r ? 'b' : 'a');
        }
        std::cout << '\n';
    }
    return 0;
}