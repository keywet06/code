#include <bits/stdc++.h>
const int N = 2005;
int n, m;
int a[N], b[N], c[N];
int main() {
    register int now;
    register long long ans;
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    for (int i = 1; i <= n; ++i) std::cin >> b[i];
    a[0] = -1;
    b[0] = 1;
    now = 0;
    while ((now = ((c[now] ^= 1) ? now - a[now] : now + b[now])) <= n) ++ans;
    std::cout << (++ans) % 998244353 << std::endl;
    return 0;
}