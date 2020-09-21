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
template <typename _Tp>
_Tp &mad(_Tp &x, _Tp y);
template <typename _Tp>
_Tp &mid(_Tp &x, _Tp y);
template <typename _Tp>
bool in(_Tp x, _Tp l, _Tp r);

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
}  // namespace oct

// the pre-document end

const int N = 1000005;
const int64 mod = 1000000007;

int n, x, y;
int f[N], deep[N], val[N];
int64 ans;
int64 dp[N], pre[N], re[N], inv[N], vi[N];
std::vector<int> to[N];

inline int ran() { return rand() << 16 ^ rand(); }
inline int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }
inline void addedge(int x, int y) {
    to[x].push_back(y);
    to[y].push_back(x);
}
inline void dfs(int u, int f) {
    deep[u] = deep[f] + 1;
    vi[deep[u]] = val[u];
    int64 t = 0;
    for (int i = 1; i <= deep[u]; ++i) {
        t += dp[deep[u] - i + 1] * vi[i] % mod * pre[n] % mod * re[deep[u] - i + 1] % mod;
    }
    ans += val[u] * pre[n] % mod;
    ans += t % mod;
    for (auto v : to[u]) {
        if (v == f) continue;
        dfs(v, u);
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n;
    for (int i = 1; i < n; ++i) std::cin >> x >> y, addedge(x, y);
    for (int i = 1; i <= n; ++i) std::cin >> val[i];
    pre[0] = 1;
    for (int i = 1; i <= n; ++i) pre[i] = pre[i - 1] * i % mod;
    inv[1] = 1;
    for (int i = 2; i <= n; ++i) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    re[0] = 1;
    for (int i = 1; i <= n; ++i) re[i] = re[i - 1] * inv[i] % mod;
    dp[0] = 1, dp[1] = 1;
    for (int i = 2; i <= 1000; ++i) {
        dp[i] = dp[i - 1] * (i - 1) % mod;
        for (int j = 0; j < i; ++j) {
            dp[i] += dp[j] * pre[i - 1] % mod * re[j] % mod;
        }
        dp[i] %= mod;
    }
    dfs(1, 1);
    std::cout << ans % mod << std::endl;
    return 0;
}