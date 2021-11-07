#include <bits/stdc++.h>

using int64 = long long;

const int D = 3;
const int N = 1000005;
const int P = 998244353;

template <typename _Tp1, typename _Tp2>
inline _Tp1 mul(_Tp1 x, _Tp2 y) {
    return x * y % P;
}

template <typename _Tp1, typename _Tp2, typename... Args>
inline _Tp1 mul(_Tp1 x, _Tp2 y, Args... args) {
    return mul(mul(x, y), args...);
}

int n, x;
int a[D];

int64 ans;
int64 fac[N], inv[N], caf[N];

std::unordered_map<int, int> map;

inline int64 C(int64 m, int64 n) {
    if (m < n || n < 0 || m < 0) return 0;
    return mul(fac[m], caf[n], caf[m - n]);
}

inline int64 solve(int n, int m, int64 k) {
    if (n <= 1) return fac[std::max(n + m - 1, 0)];
    return mul(C(m - n * k + n - 1, n - 1), fac[n - 1], fac[m]);
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    fac[0] = inv[0] = inv[1] = caf[0] = 1;
    for (int i = 1; i < N; ++i) fac[i] = mul(fac[i - 1], i);
    for (int i = 2; i < N; ++i) inv[i] = mul(P - P / i, inv[P % i]);
    for (int i = 1; i < N; ++i) caf[i] = mul(caf[i - 1], inv[i]);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> x, ++map[x], ++a[x % D];
    ans = mul(fac[a[0]], fac[a[1]], fac[a[2]], C(n - 1, a[0]));
    for (auto p : map) ans = mul(ans, caf[p.second]);
    std::cout << (std::abs(a[1] - a[2]) > 2 || a[1] == a[2] ? 0 : ans) << '\n';
    return 0;
}