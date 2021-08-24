#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>

using int64 = long long;

namespace oct {

inline int read() {
    char ch = getchar();
    int x = 0;
    while (ch < '0' || ch > '9') ch = getchar();
    x = ch - '0', ch = getchar();
    while ('0' <= ch && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    return x;
}

inline int64 qpow(const int64 x, const int64 y, const int64 P) {
    return y ? qpow(x * x % P, y / 2, P) * (y & 1 ? x : 1) % P : 1;
}

} // namespace oct

const int N = 10000005;
const int64 P = 998244353;

int64 T, n, vn, pre, ans;
int64 k[N];

int main() {
    T = oct::read();
    while (T--) {
        n = oct::read();
        if (k[n]) {
            std::cout << k[n] << '\n';
            continue;
        }
        vn = oct::qpow(n, P - 2, P);
        pre = 1, ans = 0;
        for (int i = 1; i <= n; ++i) {
            pre = pre * (n - i + 1) % P * vn % P;
            ans += pre * i % P * vn % P * (i + 1) % P;
        }
        std::cout << (k[n] = ans % P) << '\n';
    }
    return 0;
}