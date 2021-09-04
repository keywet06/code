#include <bits/stdc++.h>

#define Deb std::cerr
#define Debug Deb << "[Debug] at Line" << __LINE__ << ": "

const int N = 100005;
const int M = 262144;

int n, q, x, y;
int ans[M];

double h[N];
double max[M];

inline int getans(int u, int l, int r, double x) {
    if (l == r) return max[u] > x;
    if (max[u] <= x) return 0;
    int mid = l + r >> 1;
    if (max[u << 1] <= x) return getans(u << 1 | 1, mid + 1, r, x);
    return ans[u] - ans[u << 1] + getans(u << 1, l, mid, x);
}

inline void modify(int u, int l, int r, int x, double y) {
    if (l == r) return void(max[u] = y);
    int mid = l + r >> 1;
    x <= mid ? modify(u << 1, l, mid, x, y)
             : modify(u << 1 | 1, mid + 1, r, x, y);
    max[u] = std::max(max[u << 1], max[u << 1 | 1]);
    ans[u] = ans[u << 1] + getans(u << 1 | 1, mid + 1, r, max[u << 1]);
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> q;
    for (int i = 1; i < M; ++i) ans[i] = 1;
    while (q--) {
        std::cin >> x >> y, h[x] = double(y) / x;
        modify(1, 1, n, x, h[x]);
        std::cout << ans[1] - (h[1] == h[0]) << '\n';
    }
    return 0;
}