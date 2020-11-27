#include <bits/stdc++.h>

using int64 = long long;

namespace oct {

inline void ios(bool enable = false, std::string s = "") {
    if (enable) {
        std::string t;
        freopen((t = s + ".in").data(), "r", stdin);
        freopen((t = s + ".out").data(), "w", stdout);
    }
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
}

}  // namespace oct

const int N = 300005;
const int V = 1000005;

int P, n, q, w, h, m, a, b, x, y;
int px[N], py[N], ph[N];

int64 ans;
int64 pa[V], pb[V];

inline int abs(int x) { return x < 0 ? -x : x; }

inline int64 sqr(int64 x) { return x * x % P; }

inline int64 ka(int64 m) {
    return m < V ? pa[m] : (m & 1 ? sqr(ka(m / 2)) * a % P : sqr(ka(m / 2)));
}

inline int64 kb(int64 m) {
    return m < V ? pb[m] : (m & 1 ? sqr(kb(m / 2)) * b % P : sqr(kb(m / 2)));
}

int main() {
    oct::ios(true, "satellite");
    std::cin >> n >> q >> w >> h >> P >> a >> b;
    pa[0] = pb[0] = 1;
    for (int i = 1; i < V; ++i) pa[i] = pa[i - 1] * a % P;
    for (int i = 1; i < V; ++i) pb[i] = pb[i - 1] * b % P;
    for (int i = 1; i <= n; ++i) std::cin >> ph[i] >> px[i] >> py[i];
    for (int i = 1; i <= q; ++i) {
        std::cin >> x >> y, ans = 0;
        for (int j = 1; j <= n; ++j) {
            ans += ph[j] * ka(abs(px[j] - x)) % P * kb(abs(py[j] - y)) % P;
        }
        std::cout << ans % P << '\n';
    }
    return 0;
}