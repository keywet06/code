#include <bits/stdc++.h>

using int64 = long long;

const int N = 100005;

int n, k;
int a[N];

int64 P, ans;
int64 pre[N], inv[N], re[N];

inline int64 C(int m, int n) { return pre[m] * re[n] % P * re[m - n] % P; }

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> k >> P;
    pre[0] = inv[0] = inv[1] = re[0] = 1;
    for (int i = 1; i <= n; ++i) pre[i] = pre[i - 1] * i % P;
    for (int i = 2; i <= n; ++i) inv[i] = (P - P / i) * inv[P % i] % P;
    for (int i = 1; i <= n; ++i) re[i] = re[i - 1] * inv[i] % P;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    std::sort(a + 1, a + n + 1);
    for (int i = k; i <= n; ++i) ans += a[i] * C(i - 1, k - 1) % P;
    for (int i = 1; i <= n - k + 1; ++i) ans -= a[i] * C(n - i, k - 1) % P;
    std::cout << (ans % P + P) % P << std::endl;
    return 0;
}