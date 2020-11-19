#include <bits/stdc++.h>

using int64 = long long;

namespace oct {

void ios();

inline void ios() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
}

}  // namespace oct

const int B = 15000005;
const int N = 300005;

int n, m, q, x, y, pos, tot, c;
int ls[B], rs[B], sm[B];
int rt[N];

std::vector<int64> v[N];

inline int Q(int x, int l, int r, int v) {
    if (l == r) return l;
    int mid = (l + r) >> 1, tmp = mid - l + 1 - sm[ls[x]];
    return v <= tmp ? Q(ls[x], l, mid, v) : Q(rs[x], mid + 1, r, v - tmp);
}

inline void U(int &x, int l, int r, int p) {
    if (!x) x = ++tot;
    sm[x]++;
    if (l == r) return;
    int mid = (l + r) >> 1;
    p <= mid ? U(ls[x], l, mid, p) : U(rs[x], mid + 1, r, p);
}

inline int64 K(int x, int64 y) {
    pos = Q(rt[n + 1], 1, c, x), U(rt[n + 1], 1, c, pos);
    int64 ans = pos <= n ? 1ll * pos * m : v[n + 1][pos - n - 1];
    return v[n + 1].push_back(y ? y : ans), ans;
}

inline int64 L(int x, int y) {
    pos = Q(rt[x], 1, c, y), U(rt[x], 1, c, pos);
    int64 ans = pos < m ? 1ll * (x - 1) * m + pos : v[x][pos - m];
    return v[x].push_back(K(x, ans)), ans;
}

int main() {
    oct::ios();
    std::cin >> n >> m >> q;
    c = std::max(n, m) + q;
    while (q--) {
        std::cin >> x >> y;
        std::cout << (y == m ? K(x, 0) : L(x, y)) << '\n';
    }
}