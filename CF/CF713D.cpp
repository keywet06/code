// oct code title CF/CF706E.cpp

#ifndef OCT_CODE_INSERT_PREx2dDOCUMENT  // oct code insert pre-document
#define OCT_CODE_INSERT_PREx2dDOCUMENT

#ifdef ONLINE_JUDGE
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#endif

#ifndef STL_BITS__2F_STDCx2Bx2Bx2FH
#define STL_BITS__2F_STDCx2Bx2Bx2FH
#include <bits/stdc++.h>
#endif

#define debug std::cerr << "Debug(" << __LINE__ << "): "
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
using pi32 = std::pair<int32, int32>;
using pi64 = std::pair<int64, int64>;

namespace oct {

/* Array tn4 is the 4-direction changes in coordinate system.
 * The directions in order is {right, up, left, down}.
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
_Tp power(_Tp x, int64 m);
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
inline _Tp power(_Tp x, int64 m) {
    return m == 1 ? x : (m & 1 ? power(x * x, m / 2) * x : power(x * x, m / 2));
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

#endif  // oct code end pre-document

const int C = 10;
const int N = 1005;
const int M = 500005;

int n, m, q;
int lg2[N];
int a[N][N];
int up[C][N][N];
int pre[C][C][N][N];

inline int calc1(int x, int y, int yy) {
    int k = lg2[yy - y + 1];
    return std::min(up[k][x][y], up[k][x][yy - (1 << k) + 1]);
}
inline int calc2(int x, int y, int xx, int yy) {
    int k1 = lg2[xx - x + 1], k2 = lg2[yy - y + 1];
    return std::max(std::max(pre[k1][k2][x][y], pre[k1][k2][xx - (1 << k1) + 1][y]),
               std::max(pre[k1][k2][x][yy - (1 << k2) + 1],
                   pre[k1][k2][xx - (1 << k1) + 1][yy - (1 << k2) + 1]));
}
int main() {
    oct::sync();
    std::cin >> n >> m;
    for (reg int i = 2; i <= n || i <= m; ++i) lg2[i] = lg2[i >> 1] + 1;
    for (reg int i = 1; i <= n; ++i) {
        for (reg int j = 1; j <= m; ++j) {
            std::cin >> a[i][j];
            up[0][i][j] = a[i][j] * (up[0][i - 1][j] + 1);
        }
        for (reg int k = 1; k <= 9; ++k) {
            for (reg int i = 1; i <= n; ++i) {
                for (reg int j = 1; j <= m - (1 << k) + 1; ++j) {
                    up[k][i][j] = std::min(up[k - 1][i][j],
                                           up[k - 1][i][j + (1 << k - 1)]);
                }
            }
        }
        for (reg int i = 1; i <= n; ++i)
            for (reg int j = 1; j <= m; ++j) {
                int l = 1, r = std::min(i, j), mid, ans = 0;
                while (l <= r) {
                    mid = l + r >> 1;
                    if (calc1(i, j - mid + 1, j) >= mid)
                        ans = mid, l = mid + 1;
                    else
                        r = mid - 1;
                }
                pre[0][0][i][j] = ans;
            }
        for (reg int k = 1; k <= 9; ++k) {
            for (reg int i = 1; i <= n; ++i)
                for (reg int j = 1; j <= m - (1 << k) + 1; ++j)
                    pre[0][k][i][j] = std::max(pre[0][k - 1][i][j],
                                          pre[0][k - 1][i][j + (1 << k - 1)]);
            for (reg int i = 1; i <= n - (1 << k) + 1; ++i)
                for (reg int j = 1; j <= m; ++j)
                    pre[k][0][i][j] = std::max(pre[k - 1][0][i][j],
                                          pre[k - 1][0][i + (1 << k - 1)][j]);
        }
        for (reg int k1 = 1; k1 <= 9; k1++)
            for (reg int k2 = 1; k2 <= 9; k2++)
                for (reg int i = 1; i <= n - (1 << k1) + 1; ++i)
                    for (reg int j = 1; j <= m - (1 << k2) + 1; ++j)
                        pre[k1][k2][i][j] =
                            std::max(pre[k1][k2 - 1][i][j],
                                pre[k1][k2 - 1][i][j + (1 << k2 - 1)]);
								std::cin >> q;
        while (q--) {
            int x, y, xx, yy;
			std::cin >> x >> y >> xx >> yy;
            int l = 1, r = std::min(xx - x + 1, yy - y + 1), mid, ans = 0;
            while (l <= r) {
                mid = l + r >> 1;
                if (calc2(x + mid - 1, y + mid - 1, xx, yy) >= mid)
                    ans = mid, l = mid + 1;
                else
                    r = mid - 1;
            }
			std::cout << ans << '\n';
        }
    }
}