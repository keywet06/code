#include <bits/stdc++.h>
const int N = 200005;
const long long p = 449;
long long n, k, tp;
long long x[N], y[N], inv[N];
std::vector<int> has[p][p];
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> k;
    register int i, j, l;
    register std::vector<int> *vec;
    for (i = 1; i <= n; ++i) {
        std::cin >> x[i] >> y[i];
        has[x[i] % p][y[i] % p].push_back(i);
    }
    inv[0] = inv[1] = 1;
    for (i = 2; i < p; ++i) inv[i] = (p - p / i) * inv[p % i] % p;
    for (i = 1; i <= n; ++i) {
        for (j = 0; j < p; ++j) {
            tp = (k % p + p - x[i] * j % p) * inv[y[i] % p] % p;
            vec = &has[j][tp];
            for (l = 0; l < vec->size(); ++l) {
                if (x[i] * x[(*vec)[l]] + y[i] * y[(*vec)[l]] == k) {
                    std::cout << i << ' ' << (*vec)[l] << std::endl;
                    return 0;
                }
            }
        }
    }
    return 0;
}