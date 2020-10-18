#ifndef OBJECT_ZHENGRUIx2fZHENGRUI1563x2eCPP  // oct code object
                                              // Zhengrui/Zhengrui1563.cpp
#define OBJECT_ZHENGRUIx2fZHENGRUI1563x2eCPP

#ifndef OCT_CODE_INSERT_PREx2dDOCUMENT  // oct code insert pre-document
#define OCT_CODE_INSERT_PREx2dDOCUMENT

#if defined(ONLINE_JUDGE) && !defined(LUOGU)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,abm,mmx,avx,tune=native")
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
class prorty_queue
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

const int N = 200005;
const int M = 30005;

class qu {
   public:
    int x, d, y, f, n;
};

int n, m, K, qn, lim;
int a[M], firp[N], secp[N];
long long ans[N];
qu q[N * 3], po[N], lx[N << 1], ly[N << 1], tmp[N * 3];

void insert(int x, int w) {
    for (; x <= lim; x += x & -x) a[x] += w;
    return;
}
int ask(int x) {
    int ans = 0;
    for (; x; x -= x & -x) ans += a[x];
    return ans;
}
void solve(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    solve(l, mid);
    solve(mid + 1, r);
    int j = l, k = l;
    for (int i = mid + 1; i <= r; i++) {
        while (j <= mid && q[j].d <= q[i].d) {
            tmp[k++] = q[j];
            if (q[j].f == -2) insert(q[j].y, 1);
            j++;
        }
        if (q[i].f != -2) {
            firp[q[i].n] -= (ask(q[i].y) - ask(q[i].d)) * q[i].f;
        }
        tmp[k++] = q[i];
    }
    for (int i = l; i < j; i++) {
        if (q[i].f == -2) insert(q[i].y, -1);
    }
    for (int i = j; i <= mid; i++) tmp[k++] = q[i];
    for (int i = l; i <= r; i++) q[i] = tmp[i];
    return;
}
int cmp1(const qu &a, const qu &b) {
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}
int cmp2(const qu &a, const qu &b) {
    return a.x == b.x ? a.f < b.f : a.x < b.x;
}

int main() {
    oct::sync();
    std::cin >> n >> m >> K >> qn;
    for (int i = 1; i <= K; i++) std::cin >> po[i].x >> po[i].y, po[i].f = -2;
    std::sort(po + 1, po + K + 1, cmp1);
    for (int i = 1; i <= K; i++) {
        po[i].d = po[i - 1].x == po[i].x ? po[i - 1].y : 0;
    }
    int qxn = 0, qyn = 0, tqn = 0;
    for (int i = 1; i <= qn; i++) {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        if (x1) lx[++qxn] = (qu){x1 - 1, y1 - 1, y2, -1, i};
        lx[++qxn] = (qu){x2, y1 - 1, y2, 1, i};
        if (y1) ly[++qyn] = (qu){y1 - 1, x1 - 1, x2, -1, i};
        ly[++qyn] = (qu){y2, x1 - 1, x2, 1, i};
        firp[i] = x2 - x1 + 1;
        secp[i] = y2 - y1 + 1;
        ans[i] = 1ll * (x2 - x1 + 1) * (y2 - y1 + 1);
    }
    for (int i = 1; i <= K; i++) q[++tqn] = po[i];
    for (int i = 1; i <= qxn; i++) q[++tqn] = lx[i];
    std::sort(q + 1, q + tqn + 1, cmp2);
    lim = m;
    solve(1, tqn);
    for (int i = 1; i <= K; i++) std::swap(po[i].x, po[i].y);
    std::sort(po + 1, po + K + 1, cmp1);
    for (int i = 1; i <= K; i++) {
        po[i].d = po[i - 1].x == po[i].x ? po[i - 1].y : 0;
    }
    tqn = 0;
    std::swap(firp, secp);
    for (int i = 1; i <= K; i++) q[++tqn] = po[i];
    for (int i = 1; i <= qyn; i++) q[++tqn] = ly[i];
    std::sort(q + 1, q + tqn + 1, cmp2);
    lim = n;
    solve(1, tqn);
    for (int i = 1; i <= qn; i++) {
        std::cout << ans[i] - 1ll * firp[i] * secp[i] << '\n';
    }
    return 0;
}

#endif  // oct code end Zhengrui/Zhengrui1563.cpp
