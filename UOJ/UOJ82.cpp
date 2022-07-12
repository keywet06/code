#include <bits/stdc++.h>

using int64 = long long;

const int N = 20;
const int M = 42000;

int n, l;

int64 m;
int64 f[M];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n >> m;
    l = 1, f[0] = 1;
    for (int i = 2; i <= n; ++i) {
        int Flag = true;
        for (int j = 2; j < i; ++j) Flag &= bool(i % j);
        if (!Flag) continue;
        int t = n / i, c = t;
        while (t) c += t /= i;
        int64 b = i;
        for (int j = 1; j <= c; ++j, b *= i) {
            for (int k = 0; k < l; ++k) f[j * l + k] = f[k] * b;
        }
        l *= c + 1;
    }
    std::sort(f, f + l, [](int64 a, int64 b) { return a > b; });
    int a = 0;
    while (m) {
        while (f[a] > m) ++a;
        std::cout << f[a] << '\n', m -= f[a];
    }
    return 0;
}