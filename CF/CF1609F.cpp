#include <bits/stdc++.h>

using int64 = long long;
using pair = std::pair<int, int>;

template <typename _Tp>
using r_priority_queue =
    std::priority_queue<_Tp, std::vector<_Tp>, std::greater<_Tp> >;

const int B = 30;
const int C = 4;
const int D = (1 << B) - 1;
const int N = 1000005;
const int M = 2097152;

int n, x;
int p[N], lmin[N], rmin[N], lmax[N], rmax[N];
int sum[M], plus[M];

int64 ans;
int64 a[N];

r_priority_queue<pair> q;

std::vector<int> di[C];

std::set<int> set;
std::set<int>::iterator it;

inline int pc(int64 x) {
    return __builtin_popcount(x >> 30) + __builtin_popcount(x & D);
}

inline void update(int u, int l, int r, int x, int y, int v) {
    if (l >= x && r <= y) return sum[u] += (r - l + 1) * v, void(plus[u] += v);
    int mid = l + r >> 1;
    if (x <= mid) update(u << 1, l, mid, x, y, v);
    if (y > mid) update(u << 1 | 1, mid + 1, r, x, y, v);
    sum[u] = sum[u << 1] + sum[u << 1 | 1] + (r - l + 1) * plus[u];
}

inline int query(int u, int l, int r, int x, int y) {
    if (l >= x && r <= y) return sum[u];
    int mid = l + r >> 1, ret = (std::min(r, y) - std::max(l, x) + 1) * plus[u];
    if (x <= mid) ret += query(u << 1, l, mid, x, y);
    if (y > mid) ret += query(u << 1 | 1, mid + 1, r, x, y);
    return ret;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n, a[0] = -1;
    for (int i = 1; i <= n; ++i) std::cin >> a[i], di[pc(a[i])].push_back(i);
    for (int i = 1; i <= n; ++i) p[i] = i;
    std::sort(p + 1, p + n + 1, [](int x, int y) { return a[x] < a[y]; });
    set.insert(0), set.insert(n + 1);
    for (int i = 1; i <= n; ++i) {
        it = set.upper_bound(p[i]);
        rmin[p[i]] = *it - 1, lmin[p[i]] = *--it + 1;
        // if (a[p[i]] == a[p[i - 1]]) continue;
        set.insert(p[i]);
        // for (int j = i - 1; a[p[j]] == a[p[j + 1]]; --j) set.insert(p[j]);
    }
    set.clear();
    std::sort(p + 1, p + n + 1, [](int x, int y) { return a[x] > a[y]; });
    set.insert(0), set.insert(n + 1);
    for (int i = 1; i <= n; ++i) {
        it = set.upper_bound(p[i]);
        rmax[p[i]] = *it - 1, lmax[p[i]] = *--it + 1;
        // if (a[p[i]] == a[p[i - 1]]) continue;
        set.insert(p[i]);
        // for (int j = i - 1; a[p[j]] == a[p[j + 1]]; --j) set.insert(p[j]);
    }
    set.clear();
    for (int c = 0; c < C; ++c) {
        for (int u : di[c]) {
            ans += query(1, 1, n, lmax[u], u) * int64(rmax[u] - u + 1);
            update(1, 1, n, lmin[u], u, 1);
            q.emplace(rmin[u], u);
            while (!q.empty() && q.top().first <= u) {
                x = q.top().second, q.pop();
                update(1, 1, n, lmin[x], x, -1);
            }
            std::cout << ans << ' ';
        }
        while (!q.empty()) {
            x = q.top().second, q.pop();
            update(1, 1, n, lmin[x], x, -1);
        }
        std::cout << ans << std::endl;
        for (int i = 1; i <= n; ++i) std::cout << query(1, 1, n, i, i) << ' ';
        std::cout << std::endl;
        for (int u : di[c]) {
            ans += query(1, 1, n, lmin[u], u) * int64(rmin[u] - u + 1);
            update(1, 1, n, lmax[u], u, 1);
            q.emplace(rmax[u], u);
            while (!q.empty() && q.top().first <= u) {
                x = q.top().second, q.pop();
                update(1, 1, n, lmax[x], x, -1);
            }
            std::cout << ans << ' ';
        }
        std::cout << ans << std::endl;
        while (!q.empty()) {
            x = q.top().second, q.pop();
            update(1, 1, n, lmax[x], x, -1);
        }
        std::cout << c << ": ";
        for (int x : di[c]) std::cout << x << ' ';
        std::cout << std::endl;
    }
    std::cout << ans + n << std::endl;
    return 0;
}