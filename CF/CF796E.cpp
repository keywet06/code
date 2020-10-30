// oct code object CF/CF796E.cpp
#ifndef OCT_CODE_OBJECT_CFx2fCF796Ex2eCPP
#define OCT_CODE_OBJECT_CFx2fCF796Ex2eCPP

// oct code object pre-document.cpp
#ifndef OCT_CODE_OBJECT_PREx2dDOCUMENTx2eCPP
#define OCT_CODE_OBJECT_PREx2dDOCUMENTx2eCPP

#if defined(ONLINE_JUDGE) && !defined(LUOGU)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,abm,mmx,avx,tune=native")
#endif

// oct code object stl/bits/stdc++.h
#ifndef OCT_CODE_OBJECT_STL_BITSx2fSTDCx2bx2bx2fH
#define OCT_CODE_OBJECT_STL_BITSx2fSTDCx2bx2bx2fH
#include <bits/stdc++.h>
#endif  // oct code end stl/bits/stdc++.h

#define debug std::cerr << "Debug(" << __LINE__ << "): "
#ifdef ONLINE_JUDGE
#define cerr cout
#endif
#define pub push_back
#define pob pop_back
#define pup push
#define mkp make_pair
#define fir first
#define sec second
#define ite iterator
#define lob lower_bound
#define upb upper_bound
#define reg register

using uint8 = unsigned char;
using uint16 = unsigned short int;
using uint32 = unsigned int;
using uint64 = unsigned long long;
using int8 = signed char;
using int16 = short int;
using int32 = int;
using int64 = long long;
using ldb = long double;
using pi5 = std::pair<int32, int32>;
using pi6 = std::pair<int64, int64>;
using pi56 = std::pair<int32, int64>;
using pi65 = std::pair<int64, int32>;

namespace oct {

template <typename _Tp>
class priority_queue
    : public std::priority_queue<_Tp, std::vector<_Tp>, std::greater<_Tp> > {};

/* Array tn4 is the 4-direction changes in coordinate system.
 * The directions in order is {rght, up, left, down}.
 */
const int tn4[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
const int tn8[8][2] = {{1, 0},  {1, 1},   {0, 1},  {-1, 1},
                       {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
const double exp = 1e-8;

void sync(int pre = 8);
template <typename _Tp>
_Tp &mad(_Tp &x, _Tp y);
template <typename _Tp>
_Tp &mid(_Tp &x, _Tp y);
template <typename _Tp>
bool in(_Tp x, _Tp l, _Tp r);
template <typename _Tp>
bool in(_Tp x, _Tp y, _Tp l, _Tp r);
template <typename _Tp>
_Tp sqr(_Tp x);
template <typename _Tp>
_Tp power(_Tp x, int64 tm);
template <typename _Tp>
void sort(_Tp &x, _Tp &y);
template <typename _Tp1, typename _Tp2>
std::pair<_Tp1, _Tp2> operator+(std::pair<_Tp1, _Tp2> x,
                                std::pair<_Tp1, _Tp2> y);
template <typename _Tp>
_Tp &operator+=(_Tp &x, _Tp y);
template <typename _Tp>
_Tp gcd(_Tp &x, _Tp &y);

inline void sync(int pre) {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cout.flags(std::ios::fixed);
    std::cout.precision(pre);
    std::cout.setf(std::ios::showpoint);
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
inline bool in(_Tp x, _Tp y, _Tp l, _Tp r) {
    return l <= x && y <= r;
}
template <typename _Tp>
inline _Tp sqr(_Tp x) {
    return x * x;
}
template <typename _Tp>
inline _Tp power(_Tp x, int64 tm) {
    return tm == 1 ? x
                   : (tm & 1 ? power(x * x, tm / 2) * x : power(x * x, tm / 2));
}
template <typename _Tp>
inline void sort(_Tp &x, _Tp &y) {
    if (x > y) std::swap(x, y);
}
template <typename _Tp1, typename _Tp2>
inline std::pair<_Tp1, _Tp2> operator+(std::pair<_Tp1, _Tp2> x,
                                       std::pair<_Tp1, _Tp2> y) {
    return x.fir += y.fir, x.sec += y.sec, x;
}
template <typename _Tp>
inline _Tp &operator+=(_Tp &x, _Tp y) {
    return x = x + y;
}
template <typename _Tp>
inline _Tp gcd(_Tp &x, _Tp &y) {
    return std::__gcd(x, y);
}

}  // namespace oct

#endif  // oct code end pre-document.cpp

const int B = 2;
const int N = 1005;
const int M = 60;

int n, p, K, x, y;
int a[N], b[N];
int dp[B][N][M][M];

inline void update(int &now, int &pre, int i, int j, int k, int l) {}

int main() {
    oct::sync();
    std::cin >> n >> p >> K;
    std::cin >> x;
    for (int i = 1; i <= x; ++i) std::cin >> y, a[y] = 1;
    std::cin >> x;
    for (int i = 1; i <= x; ++i) std::cin >> y, b[y] = 1;
    if (p * K >= (n << 1)) {
        int ans = 0;
        for (int i = 1; i <= n; ++i) ans += a[i] | b[i];
        return std::cout << ans << std::endl, 0;
    }
    memset(dp, -0x3f, sizeof(dp));
    dp[0][0][0][0] = 0;
    register int i, j, k, l, tmp, now, pre, tk, tl, t;
    for (int i = 1; i <= n; ++i) {
        now = i & 1, pre = now ^ 1;
        memset(dp[now], -0x3f, sizeof(dp[now]));
        for (j = 0; j <= p; ++j) {
            for (k = 0; k <= K; ++k) {
                for (l = 0; l <= K; ++l) {
                    tmp = dp[pre][j][k][l], t = a[i] | b[i];
                    tk = std::max(k - 1, 0), tl = std::max(l - 1, 0);
                    oct::mad(dp[now][j][tk][tl], tmp);
                    if (k) oct::mad(dp[now][j][k - 1][tl], tmp + a[i]);
                    oct::mad(dp[now][j + 1][K - 1][tl], tmp + a[i]);
                    if (l) oct::mad(dp[now][j][tk][l - 1], tmp + b[i]);
                    oct::mad(dp[now][j + 1][tk][K - 1], tmp + b[i]);
                    if (k && l) oct::mad(dp[now][j][k - 1][l - 1], tmp + t);
                    if (k) oct::mad(dp[now][j + 1][k - 1][K - 1], tmp + t);
                    if (l) oct::mad(dp[now][j + 1][K - 1][l - 1], tmp + t);
                    oct::mad(dp[now][j + 2][K - 1][K - 1], tmp + t);
                }
            }
        }
    }
    int ans = 0;
    for (int j = 0; j <= p; ++j) {
        for (int k = 0; k <= K; ++k) {
            for (int l = 0; l <= K; ++l) oct::mad(ans, dp[n & 1][j][k][l]);
        }
    }
    std::cout << ans << std::endl;
    return 0;
}

#endif  // oct code end CF/CF796E.cpp