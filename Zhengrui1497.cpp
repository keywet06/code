#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
const int N = 200005;
const long long mod = 998244353;
int n;
long long ans;
long long inv[N], a[N], b[N], data[N], pre[N], re[N];
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    inv[1] = 1;
    for (int i = 2; i < N; ++i) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    pre[0] = 1;
    for (int i = 1; i < N; ++i) pre[i] = pre[i - 1] * i % mod;
    re[0] = 1;
    for (int i = 1; i < N; ++i) re[i] = re[i - 1] * inv[i] % mod;
    std::cin >> n;
    for (int i = 1; i <= n; ++i) std::cin >> a[i] >> b[i];
    for (int i = 1; i <= n; ++i) {
        data[i] = pre[a[i] + b[i]] * re[a[i]] % mod * re[b[i]] % mod;
        ans += data[i];
    }
    std::cout << ans % mod;
    for (int i = 1; i < n; ++i) {
        ans = 0;
        for (int j = 1; j <= n; ++j) {
            if (!data[j]) continue;
            ans += data[j] =
                data[j] * inv[a[j] + b[j] - i + 1] % mod * (b[j] - i + 1) % mod;
        }
        std::cout << ' ' << ans % mod;
    }
    std::cout << std::endl;
    return 0;
}