#include <bits/stdc++.h>
long long mod;
int T;
int n, m, k, i, v;
long long power(long long x, int y) {
    return y ? power(x * x % mod, y >> 1) * (y & 1 ? x : 1) % mod : 1;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> T;
	while (T--) {
        std::cin >> n >> m >> k >> i >> v >> mod;
        std::cout << v * power(2, k - 1) % mod << std::endl;
	}
	return 0;
}