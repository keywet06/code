#include <bits/stdc++.h>

using int32 = int;
using int64 = long long;
using i5 = int32;
using i6 = int64;
using pi5 = std::pair<int, int>;

namespace oct {

void ios();

inline void ios() {
    std::ios::sync_with_stdio();
    std::cin.tie(0), std::cout.tie(0);
}

}  // namespace oct


const int C = 5;
const int N = 100005;
const int P = 1000000007;

struct edge {
    int to, nxt;
} e[N];

int n, m, q, t1, t2, t3, t4, t5, cnt, tmp, ans;
int u[N], fg[N], v[N], be[N], d[N];
int kn[C], kt[C];
pi5 val[N];

inline void add(int x, int y) { e[++cnt] = (edge){y, be[x]}, be[x] = cnt; }
inline int W(int x, int y) {
    if (y < 0) return 0;
    int ret = 1;
    while (y) y& 1 ? ret = 1ll * ret * x % P : 0, x = 1ll * x * x % P, y >>= 1;
    return ret;
}
inline int b2(int x) { return (1ll * x * (x - 1) >> 1) % P; }
inline int b3(int x) { return 1ll * x * (x - 1) * (x - 2) / 6 % P; }

int main() {
    oct::ios();
    std::cin >> n >> m >> q;
    for (int i = 1; i <= m; ++i) std::cin >> u[i] >> v[i], ++d[u[i]], ++d[v[i]];
    kn[1] = 1ll * m * W(2, n - 2) % P;
    for (int i = 1; i <= n; ++i) (t1 += b2(d[i])) >= P ? t1 -= P : 0;
    kn[2] = (1ll * t1 * W(2, n - 3) + 1ll * (b2(m) - t1 + P) * W(2, n - 4)) % P;
    tmp = t1, t1 = t2 = 0;
    for (int i = 1; i <= n; ++i) val[i] = (pi5){d[i], i};
    for (int i = 1; i <= m; ++i) {
        val[u[i]] > val[v[i]] ? add(u[i], v[i]) : add(v[i], u[i]);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = be[i]; j; j = e[j].nxt) fg[e[j].to] = i;
        for (int j = be[i]; j; j = e[j].nxt) {
            for (int k = be[e[j].to]; k; k = e[k].nxt) t1 += (fg[e[k].to] == i);
        }
    }
    for (int i = 1; i <= m; ++i) {
        t2 = (t2 + 1ll * (d[u[i]] - 1) * (d[v[i]] - 1)) % P;
    }
    t2 = ((t2 - 3 * t1) % P + P) % P;
    for (int i = 1; i <= n; ++i) (t3 += b3(d[i])) >= P ? t3 -= P : 0;
    t4 = ((1ll * tmp * (m - 2) - 3ll * t3 - (t2 << 1) - 3 * t1) % P + P) % P,
    t5 = ((1ll * b3(m) - t1 - t2 - t3 - t4) % P + P) % P;
    kn[3] = (1ll * t1 * W(2, n - 3) + 1ll * t2 * W(2, n - 4) +
             1ll * t3 * W(2, n - 4) + 1ll * t4 * W(2, n - 5) +
             1ll * t5 * W(2, n - 6)) %
            P;
    if (q == 1) {
        kt[1] = 1;
    } else if (q == 2) {
        kt[1] = 1, kt[2] = 2;
    } else {
        kt[1] = 1, kt[2] = kt[3] = 6;
    }
    for (int i = 1; i <= q; ++i) ans = (ans + 1ll * kt[i] * kn[i]) % P;
    std::cout << ans << std::endl;
    return 0;
}