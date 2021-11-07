#include <bits/stdc++.h>

using int64 = long long;

const int N = 500000;

int64 n, P, x = 1, y;
int64 ps[N];

std::map<int64, int64> map;

inline int64 power(int64 x, int64 y, const int64 P) {
    int64 ret = 1;
    while (y) {
        if (y & 1) ret = ret * x % P;
        x = x * x % P, y >>= 1;
    }
    return ret;
}

inline int64 pre4(int64 x) {
    return (power(4, x, P * 3) + P * 3 - 1) % (P * 3) / 3;
}

inline int64 pow2(int64 x) { return power(2, x, P); }

inline int64 S(int64 x) {
    if (x < N) return ps[x];
    if (map.count(x)) return map[x];
    int64 c, ret = pre4(x), t = 1;
    for (c = 2; c * c < x; ++c) ret -= (t = t * 2 % P) * S(x / c) % P;
    for (c = x / c; c; --c) ret -= (pow2(x / c) - pow2(x / (c + 1))) * S(c) % P;
    return map[x] = (ret % P + P) % P;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> P;
    for (int i = 1; i < N; ++i) {
        y = ps[i] = (P + x - ps[i] % P) % P, x = x * 4 % P;
        for (int j = i << 1; j < N; j += i) ps[j] += y = y * 2 % P;
    }
    for (int i = 2; i < N; ++i) ps[i] = (ps[i] + ps[i - 1]) % P;
    std::cout << S(n) << std::endl;
    return 0;
}