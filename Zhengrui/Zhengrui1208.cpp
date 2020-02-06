#include <bits/stdc++.h>
const long long mod = 998244353;
const long long __1_ex_2 = mod + 1 >> 1;
const int K = 60;
const int Kp = K + 5;
int T, n;
long long x;
long long f[Kp];
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> T;
    f[1] = 2;
    for (int i = 2; i <= K; ++i) {
        f[i] = ((f[i - 1] + f[1]) * __1_ex_2 + 1) % mod;
    }
    while (T--) {
        std::cin >> x >> x;
        for (n = 1; 1ll << n <= x; ++n);
        std::cout << f[n] << std::endl;
    }
    return 0;
}