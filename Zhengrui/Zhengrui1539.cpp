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

const int N = 200005;
const int M = 400005;
const int K = 5000005;

void pushdown(int &u, int &l, int &r, int &mid);
void update(int u, int l, int r, int x, int y, int z);
int64 query(int u, int l, int r, int x, int y);
void finish(int u, int l, int r);
int64 check(int x, int y);

int n, m, l, r, mid;
int c[N], so[N];
int64 s, t;
int64 a[N], b[N], d[N];
int64 sum[M], lazy[M];
int64 ans[K];

inline void pushdown(int &u, int &l, int &r, int &mid) {
    if (!lazy[u]) return;
    sum[u << 1] = (mid - l + 1) * lazy[u];
    sum[u << 1 | 1] = (r - mid) * lazy[u];
    lazy[u << 1] = lazy[u << 1 | 1] = lazy[u], lazy[u] = 0;
}
inline void update(int u, int l, int r, int x, int y, int z) {
    if (x <= l && r <= y) {
        lazy[u] = z;
        sum[u] = z * (r - l + 1);
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(u, l, r, mid);
    if (x <= mid) update(u << 1, l, mid, x, y, z);
    if (y > mid) update(u << 1 | 1, mid + 1, r, x, y, z);
    sum[u] = sum[u << 1] + sum[u << 1 | 1];
}
inline int64 query(int u, int l, int r, int x, int y) {
    if (x <= l && r <= y) return sum[u];
    int mid = l + r >> 1;
    int64 ans = 0;
    pushdown(u, l, r, mid);
    if (x <= mid) ans += query(u << 1, l, mid, x, y);
    if (y > mid) ans += query(u << 1 | 1, mid + 1, r, x, y);
    return ans;
}
inline void finish(int u, int l, int r) {
    if (l == r) {
        d[l] = sum[u];
        return;
    }
    int mid = l + r >> 1;
    pushdown(u, l, r, mid);
    finish(u << 1, l, mid);
    finish(u << 1 | 1, mid + 1, r);
}
inline int64 check(int x, int y) {
    return x == 1 ? 1000000000000000ll
                  : query(1, 1, n, 1, x - 1) +
                        query(1, 1, n, x - 1, x - 1) * (y - x + 1);
}

int main() {
    oct::sync();
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) std::cin >> c[i];
    for (int i = 1; i <= m; ++i) std::cin >> a[i] >> b[i], so[i] = i;
    update(1, 1, n, 1, 1, c[1]);
    s = c[1];
    for (int i = 2; i <= n; ++i) {
        s += c[i];
        l = 1, r = i - 1;
        while (l < r) {
            mid = l + r + 1 >> 1;
            if (check(mid, i) >= s) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }
        if (l == 1) {
            t = s / i;
            r = s - t * i;
        } else {
            t = (s - query(1, 1, n, 1, l - 1)) / (i - l + 1);
            r = s - query(1, 1, n, 1, l - 1) - t * (i - l + 1);
        }
        if (r) {
            update(1, 1, n, l, l + r - 1, t + 1);
            update(1, 1, n, l + r, i, t);
        } else {
            update(1, 1, n, l, i, t);
        }
    }
    finish(1, 1, n);
    std::sort(so + 1, so + m + 1, [](int x, int y) { return a[x] < a[y]; });
    l = 0;
    for (int i = 1; i <= m; ++i) {
        if (b[so[i]] == -1) {
            while (++l <= K) ans[l] = ans[l - 1] + a[so[i]];
            break;
        }
        for (int j = 1; j <= b[so[i]] && ++l <= K; ++j) {
            ans[l] = ans[l - 1] + a[so[i]];
        }
    }
    s = 0;
    for (int i = 1; i <= n; ++i) s += ans[d[i]];
    std::cout << s << std::endl;
    return 0;
}