#include <bits/stdc++.h>
const int N = 100005;
const int N2 = N << 1;
int n, m, r1, r2, c1, c2;
int sum[N2];
int p[N];
inline void plus(int u, int l, int r, int x, int y) {
    sum[u] += y;
    if (l == r) return;
    int mid = l + r >> 1;
    x <= mid ? plus(u << 1, l, mid, x, y) : plus(u << 1 | 1, mid + 1, r, x, y);
}
inline int query(int u, int l, int r, int x, int y) {
    if (x <= l && r <= y) return sum[u];
    int mid = l + r >> 1, ans = 0;
    ans += x <= mid ? query(u << 1, l, mid, x, y) : 0;
    ans += x > mid ? query(u << 1 | 1, mid + 1, r, x, y) : 0;
    return ans;
}
inline long long answer(int r1, int r2, int c1, int c2) {
    long long ans = 0;
    for (int i = r1; i <= r2; ++i) {
        if (p[i] < c1 || c2 < p[i]) continue;
        ans += query(1, 1, n, 1, p[i]);
        plus(1, 1, n, p[i], 1);
    }
    for (int i = r1; i <= r2; ++i) {
        if (p[i] < c1 || c2 < p[i]) continue;
        plus(1, 1, n, p[i], -1);
    }
    return ans;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) std::cin >> p[i];
    if (n > 5000 || m > 5000) {
        long long ans = answer(1, n, 1, n);
        for (int i = 1; i <= m; ++i) std::cout << ans << '\n';
    }
    for (int i = 1; i <= n; ++i) {
        std::cin >> r1 >> r2 >> c1 >> c2;
        std::cout << answer(r1, r2, c1, c2) << '\n';
    }
    return 0;
}