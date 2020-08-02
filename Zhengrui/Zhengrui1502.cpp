#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
const int mod = 998244353;
const int N = 100005;
class Int {
   public:
    long long num;
    std::set<long long> s;
    inline Int() { num = 0; }
    inline Int(int x) { num = 0; }
};
int n, x, y;
long long val[N];
Int max;
Int dp[N];
std::vector<int> to[N];
inline Int operator+(Int x, Int y) {
    Int z;
    register long long i;
    z.s = x.s;
    z.num = (x.num + y.num) % mod;
    for (auto it : y.s) {
        for (i = it; z.s.count(i); ++i) z.s.erase(i);
        z.s.insert(i);
    }
    return z;
}
inline Int &operator+=(Int &x, Int y) { return x = x + y; }
inline int operator<(Int x, Int y) {
    std::set<long long>::reverse_iterator xt = x.s.rbegin(), yt = y.s.rbegin();
    for (; xt != x.s.rend() && yt != y.s.rend(); ++xt, ++yt) {
        if (*xt != *yt) return *xt < *yt;
    }
    return xt == x.s.rend();
}
inline long long power(long long x, int y) {
    return y ? power(x * x % mod, y / 2) * (y & 1 ? x : 1) % mod : 1;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n;
    for (int i = 2; i <= n; ++i) {
        std::cin >> x >> y;
        to[x].push_back(i);
        val[i] = y;
    }
    for (int i = n; i; --i) {
        if (i > 1) {
            dp[i].num = power(2, val[i]);
            dp[i].s.insert(val[i]);
        }
        max = 0;
        for (auto u : to[i]) {
            dp[i] += dp[u];
            max = std::max(max, dp[u]);
        }
        if (to[i].size()) dp[i] += max;
    }
    std::cout << dp[1].num << std::endl;
    return 0;
}