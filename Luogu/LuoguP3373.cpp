// oct code object Luogu/LuoguP3373.cpp
#ifndef OCT_CODE_OBJECT_LUOGUx2fLUOGUP3373x2eCPP
#define OCT_CODE_OBJECT_LUOGUx2fLUOGUP3373x2eCPP
#define LUOGU

// oct code object pre-document
#ifndef OCT_CODE_OBJECT_PREx2dDOCUMENT
#define OCT_CODE_OBJECT_PREx2dDOCUMENT

#if defined(ONLINE_JUDGE) && !defined(LUOGU)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,abm,mmx,avx,tune=native")
#endif

// oct code object stl/bits/stdc++.h
#ifndef OCT_CODE_OBJECT_STLx2fBITSx2fSTDCx2bx2bx2fH
#define OCT_CODE_OBJECT_STLx2fBITSx2fSTDCx2bx2bx2fH
#include <bits/stdc++.h>
#endif  // oct code end stl/bits/stdc++.h

#define debug std::cerr << "Debug(" << __LINE__ << "): "
#ifdef ONLINE_JUDGE
#define cerr cout
#endif
#define pub push_back
#define pob pop_back
#define pup push
#define mkp std::make_pair
#define fir first
#define sec second
#define ite iterator
#define lob std::lower_bound
#define upb std::upper_bound
#define reg register

using uint8 = unsigned char;
using uint16 = unsigned short int;
using uint32 = unsigned int;
using uint64 = unsigned long long;
using int8 = signed char;
using int16 = short int;
using int32 = int;
using int64 = long long;
using dr = double;
using ldr = long double;
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
int tn4[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int tn8[8][2] = {{1, 0},  {1, 1},   {0, 1},  {-1, 1},
                 {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
dr exp = 1e-8;
int64 cmods[] = {998244353, 1000000007};
int64 fmods[] = {347480897 /* CCCK */};

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
_Tp inter(_Tp l1, _Tp r1, _Tp l2, _Tp r2);
template <typename _Tp>
_Tp unions(_Tp l1, _Tp r1, _Tp l2, _Tp r2);
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
    std::cerr.flags(std::ios::fixed);
    std::cerr.precision(pre);
    std::cerr.setf(std::ios::showpoint);
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
inline _Tp inter(_Tp l1, _Tp r1, _Tp l2, _Tp r2) {
    return std::max(std::min(r1, r2) - std::max(l1, l2) + 1, _Tp(0));
}
template <typename _Tp>
inline _Tp unions(_Tp l1, _Tp r1, _Tp l2, _Tp r2) {
    return std::max(std::max(r1, r2) - std::min(l1, l2) + 1, _Tp(0));
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

#endif  // oct code end pre-document

const int N = 2197152;

void pushup(int &u);
void pushdown(int &u, int &l, int &r);
void build(int u, int l, int r);
void plu(int u, int g, int64 d);
void mul(int u, int g, int64 d);
void plus(int u, int l, int r, int x, int y, int64 d);
void mult(int u, int l, int r, int x, int y, int64 d);
int64 query(int u, int l, int r, int x, int y);

int n, m, o, x, y, k, P;
int64 a[N], sum[N], ps[N], mt[N];

inline void pushup(int &u) {
    sum[u] = sum[u << 1] + sum[u << 1 | 1] % P;
}
inline void pushdown(int &u, int &l, int &r) {
    int e = l + r >> 1, ls = u << 1, rs = ls | 1;
    sum[ls] = (sum[ls] * mt[u] + ps[u] * (e - l + 1)) % P;
    mt[ls] = mt[ls] * mt[u] % P, ps[ls] = (ps[ls] * mt[u] + ps[u]) % P;
    sum[rs] = (sum[rs] * mt[u] + ps[u] * (r - e)) % P;
    mt[rs] = mt[rs] * mt[u] % P, ps[rs] = (ps[rs] * mt[u] + ps[u]) % P;
    mt[u] = 1, ps[u] = 0; 
}
inline void build(int u, int l, int r) {
    if (l == r) return void(sum[u] = a[l]);
    int e = l + r >> 1;
    build(u << 1, l, e), build(u << 1 | 1, e + 1, r), pushup(u);
}
inline void plu(int u, int g, int64 d) {
    ps[u] = (ps[u] + d) % P;
    sum[u] = (sum[u] + d * g) % P;
}
inline void mul(int u, int g, int64 d) {
    mt[u] = mt[u] * d % P;
    ps[u] = ps[u] * d % P;
    sum[u] = sum[u] * d % P;
}
inline void plus(int u, int l, int r, int x, int y, int64 d) {
    if (oct::in(l, r, x, y)) return plu(u, r - l + 1, d);
    int e = l + r >> 1;
    pushdown(u, l, r);
    if (x <= e) plus(u << 1, l, e, x, y, d);
    if (y > e) plus(u << 1 | 1, e + 1, r, x, y, d);
    pushup(u);
}
inline void mult(int u, int l, int r, int x, int y, int64 d) {
    if (oct::in(l, r, x, y)) return mul(u, r - l + 1, d);
    int e = l + r >> 1;
    pushdown(u, l, r);
    if (x <= e) mult(u << 1, l, e, x, y, d);
    if (y > e) mult(u << 1 | 1, e + 1, r, x, y, d);
    pushup(u);
}
inline int64 query(int u, int l, int r, int x, int y) {
    if (oct::in(l, r, x, y)) return sum[u];
    int e = l + r >> 1;
    pushdown(u, l, r);
    int64 ans = 0;
    if (x <= e) ans += query(u << 1, l, e, x, y);
    if (y > e) ans += query(u << 1 | 1, e + 1, r, x, y);
    return ans % P;
}

int main() {
    oct::sync();
    std::cin >> n >> m >> P;
    for (int i = 0; i < N; ++i) mt[i] = 1;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    build(1, 1, n);
    while (m--) {
        std::cin >> o >> x >> y;
        if (o <= 2) std::cin >> k, (o == 2 ? plus : mult)(1, 1, n, x, y, k);
        if (o == 3) std::cout << query(1, 1, n, x, y) << '\n';
    }
    return 0;
}

#endif  // oct code end Luogu/LuoguP3373.cpp