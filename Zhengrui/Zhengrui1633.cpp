// oct code object Zhengrui/Zhengrui1633.cpp
#ifndef OCT_CODE_OBJECT_ZHENGRUIx2fZHENGRUI1633x2eCPP
#define OCT_CODE_OBJECT_ZHENGRUIx2fZHENGRUI1633x2eCPP

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

using std::make_pair;
using pair = std::pair<int, pi5>;

const int N = 70;
const int U = N >> 2;
const int V = 1 << U;
const int M = 500;

int cnt, unt, n, m, u, v, w, a, b, inf, p, r;
int f[N], s[N], head[N], id[N];
int next[M], to[M], val[M];
int d[N][V];
pair o;
std::queue<pair> q;

inline void insert(int u, int v, int w) {
    next[++cnt] = head[u], head[u] = cnt, to[cnt] = v, val[cnt] = w;
}
inline void addedge(int u, int v, int w) { insert(u, v, w), insert(v, u, w); }
inline int find(int u) { return u == f[u] ? u : f[u] = find(f[u]); }
inline void merger(int u, int v) { s[u] += s[v] * (u != v), f[v] = u; }
inline void merge(int u, int v) { merger(find(u), find(v)); }

int main() {
    std::cin >> n >> m >> a >> b;
    for (int i = 0; i < n; ++i) f[i] = i, s[i] = 1;
    while (m--) {
        std::cin >> u >> v >> w, addedge(--u, --v, w);
        if (w == a) merge(u, v);
    }
    memset(id, -1, sizeof(id));
    for (int i = 0; i < n; ++i) {
        if (f[i] == i && s[i] > 3) id[i] = unt++;
    }
    for (int i = 0; i < n; ++i) id[i] = id[find(i)];
    memset(d, 63, sizeof(d)), inf = d[0][0];
    v = ~id[0] ? 1 << id[0] : 0;
    d[0][v] = 0, q.push(mkp(0, mkp(0, v)));
    while (q.size()) {
        o = q.front(), q.pop(), p = o.fir, u = o.sec.fir, w = o.sec.sec;
        if (d[u][w] != p) continue;
        for (int e = head[u]; e; e = next[e]) {
            if (val[e] == b && find(u) == find(to[e]) ||
                id[u] != (v = id[to[e]]) && ~v && 1 << v & w) {
                continue;
            }
            v = w | (~id[to[e]] ? 1 << id[to[e]] : 0);
            if (d[to[e]][v] <= d[u][w] + val[e]) continue;
            d[to[e]][v] = d[u][w] + val[e];
            q.push(mkp(d[to[e]][v], mkp(to[e], v)));
        }
    }
    for (int u = 0; u < n; ++u) {
        p = d[u][0];
        for (int v = 1; v < 1 << unt; ++v) oct::mid(p, d[u][v]);
        std::cout << p << ' ';
    }
    std::cout << std::endl;
    return 0;
}

#endif  // oct code end Zhengrui/Zhengrui1633.cpp
