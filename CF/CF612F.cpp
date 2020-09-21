#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
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

using uint8 = unsigned char;
using uint16 = unsigned short int;
using uint32 = unsigned int;
using uint64 = unsigned long long;
using int8 = signed char;
using int16 = short int;
using int32 = int;
using int64 = long long;
using pi32 = std::pair<int32, int32>;
using vi32 = std::vector<int32>;
using qi32 = std::queue<int32>;
using spi32 = std::set<pi32>;

namespace oct {

/* Array tn4 is the 4-direction changes in coordinate system.
 * The directions in order is {right, up, left, down}.
 */
const int tn4[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
const int tn8[8][2] = {{1, 0},  {1, 1},   {0, 1},  {-1, 1},
                       {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

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

const int N = 2005;

int dis(int x, int y);
int gsi(int i);
int last(int i, int j);
int next(int i, int j);

int n, s, q, sr;
int a[N], pr[N], d1[N], d2[N], l[N];
std::vector<int> r[N];

inline int dis(int x, int y) {
    return std::min(std::abs(x - y), std::abs(x - y - n));
}
inline int gsi(int i) { return r[i].size(); }
inline int la(int i, int j) { return j ? j - 1 : gsi(i) - 1; }
inline int ne(int i, int j) { return j + 1 < gsi(i) ? j + 1 : 0; }
inline int la(int i) { return (i ? i : n) - 1; }
inline int ne(int i) { return (i + 1) % n; }
inline int dil(int i, int j) { return n - dis(r[i][j], r[i][ne(i, j)]); }
inline int dir(int i, int j) { return n - dis(r[i][j], r[i][la(i, j)]); }
inline void write(int x) {
    if (x >= 0) std::cout << '+';
    std::cout << x << '\n';
}
inline void pri(int u, int v) {
    if (std::abs(u - v) < std::abs(u - v - n)) {
        write(v - u);
    } else {
        write(v - u > 0 ? v - u - n : v - u + n);
    }
}
inline void mto(int u) { pri(sr, u), sr = u; }
inline void tol(int u) {
    for (int i = u - 1; ~i; --i) {
        if (a[i] == a[u]) mto(i);
    }
    for (int i = n - 1; i > u; --i) {
        if (a[i] == a[u]) mto(i);
    }
}
inline void tor(int u) {
    for (int i = u + 1; i < n; ++i) {
        if (a[i] == a[u]) mto(i);
    }
    for (int i = 0; i < u; ++i) {
        if (a[i] == a[u]) mto(i);
    }
}

int main() {
    std::cin >> n >> s;
    for (int i = 0; i < n; ++i) std::cin >> a[i], pr[i] = a[i];
    std::sort(pr, pr + n);
    int q = std::unique(pr, pr + n) - pr;
    for (int i = 0; i < n; ++i) a[i] = std::lob(pr, pr + q, a[i]) - pr;
    for (int i = 0; i < n; ++i) r[a[i]].pub(i);
    memset(d1, 50, sizeof(d1));
    memset(d2, 50, sizeof(d2));
    for (int i = 0; i < gsi(q - 1); ++i) d2[r[q - 1][i]] = 0;
    for (int c = q - 1; c; --c) {
        for (int i = 0; i < gsi(c); ++i) {
            d1[r[c][i]] =
                std::min(dil(c, i) + d2[ne(c, i)], dir(c, i) + d2[la(c, i)]);
        }
        for (int u : r[c - 1]) {
            for (int v : r[c]) oct::mid(d2[u], d1[v] + dis(u, v));
        }
    }
    for (int i = 0; i < gsi(0); ++i) {
        d1[r[0][i]] =
            std::min(dil(0, i) + d2[ne(0, i)], dir(0, i) + d2[la(0, i)]);
    }
    int ans = d1[N - 1];
    sr = s;
    for (int u : r[0]) {
        if (d1[u] + dis(sr, u) < ans) {
            ans = d1[u] + dis(sr, u);
            s = u;
        }
    }
    mto(s);
    std::cout << ans << std::endl;
    for (int i = 1; i <= n; ++i) write(d1[i] - n / 2);
    return 0;
}