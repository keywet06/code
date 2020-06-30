#include <bits/stdc++.h>
const int N = 50005;
int n, m, s;
int ks[N], kl[N], kr[N], a[N], so[N];
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m;
    s = int(sqrt(n));
    for (int i = 0; i < n; ++i) ks[i] = i / s, kl[i] = i * s, kr[i] = i * s + s;
    kr[n - 1] = n;
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    
    return 0;
}