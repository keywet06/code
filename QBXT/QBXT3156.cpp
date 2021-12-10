#include <bits/stdc++.h>

using int64 = long long;
using int128 = __int128;

inline std::mt19937_64 GetRand() {
    return std::mt19937_64(
        std::chrono::system_clock::now().time_since_epoch().count());
}

template <typename Type1, typename Type2, typename Type3>
inline Type1 Pow(Type1 x, Type2 y, const Type3 P) {
    Type1 Ret = 1;
    while (y) {
        if (y & 1) Ret = Ret * x % P;
        x = x * x % P, y >>= 1;
    }
    return Ret;
}

inline bool MillerRobin(int128 n, size_t TestTimes = 8) {
    if (n < 3 || n % 2 == 0) return n == 2;
    int64 e = n - 1;
    size_t m = 0;
    std::mt19937_64 rd(GetRand());
    while (!(e & 1)) e >>= 1, ++m;
    for (size_t i = 0, j; i < TestTimes; ++i) {
        int128 x = Pow(rd() % (n - 1) + 1, e, n);
        if (x == 1) continue;
        for (j = 0; j < m; ++j) {
            if (x == n - 1) break;
            if (x == 1) return false;
            x = x * x % n;
        }
        if (j == m) return false;
    }
    return true;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    int64 T, n;
    std::cin >> T;
    while (T--) {
        std::cin >> n;
        std::cout << (MillerRobin(n, 16) ? 'Y' : 'N') << '\n';
    }
    return 0;
}