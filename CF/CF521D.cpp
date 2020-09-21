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
using uint128 = __uint128_t;
using int8 = signed char;
using int16 = short int;
using int32 = int;
using int64 = long long;
using int128 = __int128_t;
using pi32 = std::pair<int32, int32>;

namespace oct {
template <typename _Tp>
_Tp &mad(_Tp &x, _Tp y);
template <typename _Tp>
_Tp &mid(_Tp &x, _Tp y);

template <typename _Tp>
_Tp &mad(_Tp &x, _Tp y) {
    return x = std::max(x, y);
}
template <typename _Tp>
_Tp &mid(_Tp &x, _Tp y) {
    return x = std::min(x, y);
}
}  // namespace oct

// the pre-document end

const int N = 100005;
struct node {
    int x;
};
int n, m, k, cnt, t, x, y;
int64 a[N], t1[N], t3[N], so[N], i1[N], ans[N];
std::vector<pi32> t2[N];
std::priority_queue<node> pq;
inline int operator<(node x, node y) {
    return t2[x.x].rbegin()->fir * a[y.x] < t2[y.x].rbegin()->fir * a[x.x];
}
inline node mkn(int x) {
    node a;
    a.x = x;
    return a;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> k >> n >> m;
    for (int i = 1; i <= k; ++i) std::cin >> a[i];
    for (int i = 1; i <= n; ++i) {
        std::cin >> t >> x >> y;
        if (t == 1) {
            if (y > t1[x]) t1[x] = y, i1[x] = i;
        } else if (t == 2) {
            t2[x].pub(std::mkp(y, i));
        } else {
            t3[i] = y;
        }
        so[i] = i;
    }
    std::sort(so + 1, so + n + 1, [](int x, int y) { return t3[x] < t3[y]; });
    for (int i = 1; i <= k; ++i) {
        if (t1[i]) t2[i].pub(std::mkp(t1[i], i1[i]));
    }
    for (int i = 1; i <= k; ++i) {
        if (!t2[i].size()) continue;
        std::sort(t2[i].begin(), t2[i].end(),
                  [](pi32 x, pi32 y) { return x.fir > y.fir; });
        pq.push(mkn(i));
    }
    cnt = 0;
    y = m - n + 1;
    while (pq.size() &&
           t2[x = pq.top().x].rbegin()->fir > (t3[cnt + y] - 1) * a[x] &&
           (pq.pop(), ++cnt <= m)) {
        ans[cnt] = t2[x].rbegin()->sec;
    }
    x = n - m + cnt - 1;
    while (x <= n && !t3[so[x]]) ++x;
    while (x <= n) ans[++cnt] = so[x++];
    std::cout << cnt << std::endl;
    for (int i = 1; i <= cnt; ++i) std::cout << ans[i] << ' ';
    std::cout << std::endl;
    return 0;
}