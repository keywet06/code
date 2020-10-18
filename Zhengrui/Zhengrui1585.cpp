// oct code title Zhengrui/Zhengrui1585.cpp

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

const int B = 10;
const int N = 2005;
const int M = N << 1;

int cmp(int x, int y);
int solve(int s);
void coutans(int l, int r);
int check(int l, int r);

char str[M];
int n, k, lst, tmp;
int sum[N], id[N], f[N], ras[N], wor[N], ans[N];
int next[N][N];

inline int cmp(int x, int y) { return strcmp(str + x, str + y) < 0; }
inline int solve(int s) {
    for (int i = 0; i < n; ++i) wor[i] = std::min(n, i + ras[(s + i) % n]);
    memset(f, 0, sizeof(f)), f[n] = 1;
    for (int i = 0; i < k; ++i) {
        sum[n] = f[n];
        f[n] = 0;
        for (int j = n - 1; ~j; j--) {
            sum[j] = sum[j + 1] + f[j];
            f[j] = sum[j + 1] > sum[wor[j] + 1];
        }
    }
    return f[0];
}
inline void coutans(int l, int r) {
    memset(f, 0, sizeof(f)), f[n] = 1;
    for (int i = 0; i < n; ++i) wor[i] = std::min(n, i + ras[(lst + i) % n]);
    for (int i = 0; i < k; ++i) {
        sum[n] = f[n] ? n : 1e9, f[n] = 0;
        for (int j = n - 1; j >= 0; j--) {
            sum[j] = f[j] ? j : sum[j + 1];
            if (f[j] = (sum[j + 1] <= wor[j])) next[i][j] = sum[j + 1];
        }
    }
    for (int i = k - 1, j = 0; ~i; --i) ans[i] = (j + lst) % n, j = next[i][j];
    std::sort(ans, ans + k);
    for (int i = 0; i < k; ++i) std::cout << ans[i] + 1 << ' ';
    std::cout << std::endl;
}
inline int check(int l, int r) {
    for (int i = 0; i < n; ++i) {
        int c = 0;
        for (int j = l; j < r; ++j) {
            if (str[j - l + i] != str[j]) {
                c = str[j - l + i] < str[j] ? -1 : j - l + 1;
                break;
            }
        }
        ras[i] = c < 0 ? n : (c > 0 ? c - 1 : r - l);
    }
    int t;
    for (int i = 0; i < n; ++i) id[i] = i;
    std::random_shuffle(id, id + n);
    for (int i = 0; i < n && i < B * n / k; ++i) {
        if (solve(t = id[i])) return lst = t, 1;
    }
    return 0;
}

int main() {
    oct::sync();
    std::cin >> str >> k, n = strlen(str);
    for (int i = 0; i < n; ++i) str[i + n] = str[i];
    for (int i = 0; i < n; ++i) id[i] = i;
    std::nth_element(id, id + k - 1, id + n, cmp);
    int l = 0, r = n, s = id[k - 1], mid;
    while (l + 1 < r) (check(s, s + (mid = (l + r) >> 1)) ? r : l) = mid;
    check(s, s + r), coutans(s, s + r);
    return 0;
}