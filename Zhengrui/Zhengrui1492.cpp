#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define debug std::cerr << "Debug(" << __LINE__ << "): "
#define pub push_back
#define pob pop_back
#define mkp make_pair
#define fir first
#define sec second

using uint8 = unsigned char;
using uint16 = unsigned short int;
using uint32 = unsigned int;
using uint64 = unsigned long long;
using int8 = signed char;
using int16 = short int;
using int32 = int;
using int64 = long long;
using pi32 = std::pair<int32, int32>;

namespace oct {
void sync();
template <typename _Tp>
_Tp &mad(_Tp &x, _Tp y);
template <typename _Tp>
_Tp &mid(_Tp &x, _Tp y);
template <typename _Tp>
bool in(_Tp x, _Tp l, _Tp r);
template <typename _Tp>
_Tp sqr(_Tp x);

inline void sync() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
}
template <typename _Tp>
inline _Tp &mad(_Tp &x, _Tp y) {
    return x = std::max(x, y);
}
template <typename _Tp>
inline _Tp &mid(_Tp &x, _Tp y) {
    return x = std::min(x, y);
}
template <typename _Tp>
inline bool in(_Tp x, _Tp l, _Tp r) {
    return l <= x && x <= r;
}
template <typename _Tp>
inline _Tp sqr(_Tp x) {
    return x * x;
}
}  // namespace oct

// the pre-document end

int T, a;
int64 n, p, q;
inline int64 get(int64 x) { return x * (x + 1); }
inline bool check(int64 n) { return get(sqrt(n * 2)) == n * 2; }
int main() {
    oct::sync();
    std::cin >> T;
    while (T--) {
        std::cin >> n;
        p = n / 6;
        q = n % 6 + !(n % 6) * 6;
        if (q != 2) a = q > 2 ? q : 1 + !check(p) * 6;
        if (q == 2) {
            int tf = 0;
            for (int64 i = 1; i * (i - 1) / 2 <= p; ++i) {
                if (!check(p - i * (i - 1) / 2)) continue;
                tf = 1;
                break;
            }
            a = tf ? 2 : 8;
        }
        std::cout << a << '\n';
    }
    return 0;
}