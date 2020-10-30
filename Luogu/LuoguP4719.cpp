// oct code object Luogu/LuoguP4719.cpp
#ifndef OCT_CODE_OBJECT_LUOGUx2fLUOGUP4719x2eCPP
#define OCT_CODE_OBJECT_LUOGUx2fLUOGUP4719x2eCPP
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
int tn4[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int tn8[8][2] = {{1, 0},  {1, 1},   {0, 1},  {-1, 1},
                       {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
double exp = 1e-8;

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

#endif  // oct code end pre-document

// oct code object gmatrix.cpp
#ifndef OCT_CODE_OBJECT_GMATRIXx2eCPP
#define OCT_CODE_OBJECT_GMATRIXx2eCPP

// oct code object stl/bits/stdc++.h
#ifndef OCT_CODE_OBJECT_STL_BITSx2fSTDCx2bx2bx2fH
#define OCT_CODE_OBJECT_STL_BITSx2fSTDCx2bx2bx2fH
#include <bits/stdc++.h>
#endif  // oct code end stl/bits/stdc++.h

namespace oct {

template <typename _Tp, size_t _N, size_t _M>
class gmatrix {
   protected:
    _Tp data[_N][_M];

   public:
    gmatrix();
    gmatrix(_Tp _data[_N][_M]);
    _Tp *operator[](size_t i);
};

template <typename _Tp, size_t _N, size_t _M>
gmatrix<_Tp, _N, _M> operator+(gmatrix<_Tp, _N, _M> x,
                               gmatrix<_Tp, _N, _M> y);
template <typename _Tp, size_t _N, size_t _K, size_t _M>
gmatrix<_Tp, _N, _M> operator*(gmatrix<_Tp, _N, _K> x,
                               gmatrix<_Tp, _K, _M> y);
template <typename _Tp, size_t _N, size_t _M>
gmatrix<_Tp, _N, _M> operator*(gmatrix<_Tp, _N, _M> x, _Tp y);
template <typename _Tp, size_t _N, size_t _M>
gmatrix<_Tp, _N, _M> &operator+=(gmatrix<_Tp, _N, _M> &x,
                                 gmatrix<_Tp, _N, _M> y);
template <typename _Tp, size_t _N, size_t _K, size_t _M>
gmatrix<_Tp, _N, _M> &operator*=(gmatrix<_Tp, _N, _K> &x,
                                 gmatrix<_Tp, _K, _M> y);
template <typename _Tp, size_t _N, size_t _M>
gmatrix<_Tp, _N, _M> &operator*=(gmatrix<_Tp, _N, _M> &x, _Tp y);

template <typename _Tp, size_t _N, size_t _M>
inline gmatrix<_Tp, _N, _M>::gmatrix() {
    memset(data, 0, sizeof(data));
}
template <typename _Tp, size_t _N, size_t _M>
inline gmatrix<_Tp, _N, _M>::gmatrix(_Tp _data[_N][_M]) {
    memcpy(data, _data, sizeof(data));
}
template <typename _Tp, size_t _N, size_t _M>
inline _Tp *gmatrix<_Tp, _N, _M>::operator[](size_t i) {
    return data[i];
}
template <typename _Tp, size_t _N, size_t _M>
inline gmatrix<_Tp, _N, _M> operator+(gmatrix<_Tp, _N, _M> x,
                                      gmatrix<_Tp, _N, _M> y) {
    gmatrix<_Tp, _N, _M> ret;
    for (int i = 0; i < _N; ++i) {
        for (int j = 0; j < _M; ++j) ret[i][j] = x[i][j] + y[i][j];
    }
    return ret;
}
template <typename _Tp, size_t _N, size_t _K, size_t _M>
inline gmatrix<_Tp, _N, _M> operator*(gmatrix<_Tp, _N, _K> x,
                                      gmatrix<_Tp, _K, _M> y) {
    gmatrix<_Tp, _N, _M> ret;
    for (int i = 0; i < _N; ++i) {
        for (int j = 0; j < _M; ++j) {
            for (int k = 0; k < _K; ++k) {
                ret[i][j] = std::max(ret[i][j], x[i][k] + y[k][j]);
            }
        }
    }
    return ret;
}
template <typename _Tp, size_t _N, size_t _M>
gmatrix<_Tp, _N, _M> operator*(gmatrix<_Tp, _N, _M> x, _Tp y) {
    gmatrix<_Tp, _N, _M> ret = x;
    for (int i = 0; i < _N; ++i) {
        for (int j = 0; j < _M; ++j) ret[i][j] = ret[i][j] * y;
    }
    return ret;
}
template <typename _Tp, size_t _N, size_t _M>
inline gmatrix<_Tp, _N, _M> &operator+=(gmatrix<_Tp, _N, _M> &x,
                                        gmatrix<_Tp, _N, _M> y) {
    return x = x + y;
}
template <typename _Tp, size_t _N, size_t _K, size_t _M>
inline gmatrix<_Tp, _N, _M> &operator*=(gmatrix<_Tp, _N, _K> &x,
                                        gmatrix<_Tp, _K, _M> y) {
    return x = x * y;
}
template <typename _Tp, size_t _N, size_t _M>
gmatrix<_Tp, _N, _M> &operator*=(gmatrix<_Tp, _N, _M> &x, _Tp y) {
    return x = x * y;
}

}  // namespace oct

#endif  // oct code object gmatrix.cpp

using mat = oct::gmatrix<int64, 2, 2>;
using vec = oct::gmatrix<int64, 2, 1>;

const int N = 100005;
const int M = 262144;
const int64 INF = 10000000007;

void insert(int u, int v);
void addedge(int u, int v);

int n, m, x, y, cnt;
int dfn[N], top[N], bot[N], size[N], deep[N], son[N], fa[N], nfd[N], a[N];
mat init[N];
mat sum[M];
vec st, tsp;
std::vector<int> to[N];

inline void insert(int u, int v) { to[u].pub(v); }
inline void addedge(int u, int v) { insert(u, v), insert(v, u); }
inline void dfs1(int u, int f) {
    deep[u] = deep[fa[u] = f] + 1, size[u] = 1;
    for (int v : to[u]) {
        if (v == f) continue;
        dfs1(v, u), size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
}
inline void dfs2(int u, int t) {
    nfd[dfn[u] = ++cnt] = u, top[u] = t, bot[t] = u;
    if (son[u]) dfs2(son[u], t);
    for (int v : to[u]) {
        if (v != fa[u] && v != son[u]) dfs2(v, v);
    }
}
inline void build(int u, int l, int r) {
    if (l == r) return void(sum[u] = init[l]);
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    sum[u] = sum[u << 1] * sum[u << 1 | 1];
}
inline void update(int u, int l, int r, int x, mat d) {
    if (l == r) return void(sum[u] += d);
    int mid = l + r >> 1;
    mid <= x ? update(u << 1, l, mid, x, d)
             : update(u << 1 | 1, mid + 1, r, x, d);
    sum[u] = sum[u << 1] * sum[u << 1 | 1];
}
inline mat query(int u, int l, int r, int x, int y) {
    if (oct::in(l, r, x, y)) return sum[u];
    int mid = l + r >> 1;
    if (y <= mid) return query(u << 1, l, mid, x, y);
    if (x > mid) return query(u << 1 | 1, mid + 1, r, x, y);
    return query(u << 1, l, mid, x, y) * query(u << 1 | 1, mid + 1, r, x, y);
}
inline mat geta(int u) { return query(1, 1, n, dfn[u], bot[u]); }
inline void buildS() {
    mat tmp;
    tmp[0][0] = tmp[0][1] = 0, tmp[1][1] = -INF;
    for (int i = n, u; i; --i) {
        u = nfd[i];
        for (int v : to[u]) {
            if (v == son[u] || v == fa[u]) continue;
            sum[i] += geta(v);
        }
        tmp[1][0] = a[u], sum[i] += tmp;
    }
    build(1, 1, n);
}
inline void updateS(int u, int d) {
    int t = top[u];
    while (t > 1) update(1, 1, n, dfn[fa[t]], geta(t) * -1ll), t = top[fa[u]];
    mat tmp;
    tmp[1][0] = d - a[dfn[u]], update(1, 1, n, dfn[u], tmp), u = top[u];
    while (u > 1) update(1, 1, n, dfn[fa[u]], geta(u)), u = top[fa[u]];
}
inline vec getans() { return query(1, 1, n, 1, bot[1]) * st; }
inline int prans() { return tsp = getans(), std::max(tsp[0][0], tsp[1][0]); }

int main() {
    oct::sync();
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    for (int i = 1; i < n; ++i) std::cin >> x >> y, addedge(x, y);
    dfs1(1, 1), dfs2(1, 1), buildS();
    debug << "dfn = {0";
    for (int i = 1; i <= n; ++i) std::cerr << ", " << dfn[i];
    std::cerr << ", 0, ...};" << std::endl;
    debug << "top = {0";
    for (int i = 1; i <= n; ++i) std::cerr << ", " << top[i];
    std::cerr << ", 0, ...};" << std::endl;
    while (m--) std::cin >> x >> y, updateS(x, y), std::cout << prans() << '\n';
    return 0;
}

#endif  // oct code end Luogu/LuoguP4719.cpp
