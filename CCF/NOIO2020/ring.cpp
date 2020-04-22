#include <bits/stdc++.h>
const int N = 200005;
int n, m, k;
long long a[N], ans[N], pre[N];
inline int cmp(int x, int y) { return x > y; }
template <typename _Tp>
inline _Tp gcd(_Tp x, _Tp y) {
    return y ? gcd(y, x % y) : x;
}
inline long long getans(int k) {
    if (ans[k]) {
        return ans[k];
    }
    int t = n / k;
    for (int i = 0; i < k; ++i) {
        ans[k] += a[i * t] * a[i * t + 1] + a[i * t + t - 2] * a[i * t + t - 1];
        ans[k] += pre[i * t + t - 1] - pre[i * t + 1];
    }
    return ans[k];
}
int main() {
    freopen("ring.in", "r", stdin);
    freopen("ring.out", "w", stdout);
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        ans[0] += a[i] * a[i];
    }
    std::sort(a, a + n, cmp);
    for (int i = 2; i < n; ++i) {
        pre[i] = pre[i - 1] + a[i] * a[i - 2];
    }
    for (int i = 1; i <= m; ++i) {
        std::cin >> k;
        std::cout << (k ? getans(gcd(k, n)) : ans[0]) << "\n";
    }
    return 0;
}