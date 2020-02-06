#include <bits/stdc++.h>
const int N = 2000;
const int Np = N + 5;
int T, n;
long long s, mod;
long long as[Np];
inline int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }
inline int lcm(int x, int y) { return x * y / gcd(x, y); }
inline int gans(int x, int y) { return std::min(n, gcd(x, y) + lcm(x, y)); }
int main() {
    std::cin >> T >> mod;
    while (T--) {
        std::cin >> n;
        if (as[n]) {
            std::cout << as[n] << std::endl;
            continue;
        }
        s = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                s += gans(i, j);
            }
        }
        std::cout << (as[n] = s % mod) << std::endl;
    }
    return 0;
}