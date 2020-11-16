// oct object csp-pre-document
#ifndef OCT_OBJECT_CSPx2dPREx2dDOCUMENT
#define OCT_OBJECT_CSPx2dPREx2dDOCUMENT

#include <bits/stdc++.h>

typedef long long int64;

namespace oct {

void sync();

inline void sync() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
}

}  // namespace oct

#endif  // oct end csp-pre-document

const int N = 300005;
const int64 P = 1000000007;

void init();
int64 Bi(int m, int n);
int find(int u);

int n, q, o, x, y, ans;
int f[N], siz[N];
int64 pre[N], rei[N], dp[N];

inline void init() {
    pre[0] = rei[0] = rei[1] = 1;
    for (int i = 1; i <= n; ++i) pre[i] = pre[i - 1] * i % P;
    for (int i = 2; i <= n; ++i) rei[i] = (P - P / i) * rei[P % i] % P;
    for (int i = 2; i <= n; ++i) rei[i] = rei[i - 1] * rei[i] % P;
    for (int i = 0; i < n; ++i) f[i] = i, siz[i] = dp[i] = 1;
}
inline int64 Bi(int m, int n) { return pre[m] * rei[n] % P * rei[m - n] % P; }
inline int find(int u) { return f[u] == u ? u : f[u] = find(f[u]); }

int main() {
    oct::sync();
    std::cin >> n >> q;
    init();
    while (q--) {
        std::cin >> o >> x, x = (x + ans) % n, x = find(x);
        if (o == 1) std::cin >> y, y = (y + ans) % n, y = find(y);
        if (o == 1) {
            if (x == y) continue;
            f[x] = y, siz[y] += siz[x];
            dp[y] = dp[y] * Bi(siz[y] - 1, siz[x]) % P * dp[x] % P;
        } else {
            std::cout << (ans = dp[x]) << '\n';
        }
    }
    return 0;
}