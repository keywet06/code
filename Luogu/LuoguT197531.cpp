#include <bits/stdc++.h>

using int64 = long long;

const int P = 998244353;
const int M = (P >> 1) + 5;
const int N = (P >> 4) + 5;

struct Init {
    template <typename Callable>
    Init(Callable &&callable) {
        callable();
    }
};

template <typename _Tp1, typename _Tp2>
inline _Tp1 mul(_Tp1 x, _Tp2 y) {
    return x * y % P;
}

template <typename _Tp1, typename _Tp2, typename... Args>
inline _Tp1 mul(_Tp1 x, _Tp2 y, Args... args) {
    return mul(mul(x, y), args...);
}

template <typename _Tp1, typename _Tp2>
inline _Tp1 &mud(_Tp1 &x, _Tp2 y) {
    return x = mul(x, y);
}

template <typename _Tp1, typename _Tp2, typename... Args>
inline _Tp1 &mud(_Tp1 &x, _Tp2 y, Args... args) {
    return mud(mud(x, args...), y);
}

int64 pre[N];

Init init([]() {
    pre[0] = 1, pre[1] = 5040;
    for (register int64 i = 2, x = 8; i < N; ++i, x += 8) {
        pre[i] =
            mul(pre[i - 1], x, x | 1, x | 2, x | 3, x | 4, x | 5, x | 6, x | 7);
    }
});

inline int64 power(int64 x, int y) {
    int64 ret = 1;
    while (y) {
        if (y & 1) mud(ret, x);
        mud(x, x), y >>= 1;
    }
    return ret;
}

inline int64 inv(int64 x) { return power(x, P - 2); }

inline int64 fac(int x) {
    if (x >= P) return 0;
    if (x > M) return x & 1 ? inv(fac(P - x - 1)) : P - inv(fac(P - x - 1));
    int64 ret = pre[x >> 3], r = std::max(x >> 3 << 3, 2) - 1;
    while (++r <= x) mud(ret, r);
    return ret;
}

inline int64 C(int m, int n) {
    int64 ret = mul(fac(m), inv(mul(fac(n), fac(m - n))));
    return ret;
    return mul(fac(m), inv(mul(fac(n), fac(m - n))));
}

inline int64 solve(int u, int v, int t, int a, int b) {
    int64 p = mul(int64(a), inv(b * 2)), q = (P + inv(2) - p) % P,
          d = t - u - v >> 1;
    if ((u ^ v ^ t) & 1 || t < std::abs(u) + std::abs(v)) return 0;
    return mul(C(t, t + u - v >> 1), C(t, d), power(q, d), power(p, t - d));
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    int T, u, v, t, a, b;
    std::cin >> T;
    while (T--) {
        std::cin >> u >> v >> t >> a >> b;
        std::cout << solve(u, v, t, a, b) << '\n';
    }
    return 0;
}