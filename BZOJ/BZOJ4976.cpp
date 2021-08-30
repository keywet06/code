#include <bits/stdc++.h>

const int C = 17;
const int N = 100005;
const int M = 1 << C;

int n, k, x, d;
int f[M];

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> k;
    if (n - k >= C) {
        while (n--) std::cin >> x, d |= x;
        std::cout << d << std::endl;
    } else {
        memset(f, 63, sizeof(f));
        f[0] = 0;
        for (int i = 0; i < n; ++i) {
            std::cin >> x;
            for (int j = 0; j < M; ++j) f[j | x] = std::min(f[j | x], f[j] + 1);
        }
        for (int i = M - 1; ~i; --i) {
            if (f[i] + k <= n) {
                std::cout << i << std::endl;
                break;
            }
        }
    }
    return 0;
}