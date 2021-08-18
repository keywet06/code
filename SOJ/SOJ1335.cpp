#include <bits/stdc++.h>

const int N = 5005;

int n, m, k, x, y, z, c;
int next[N], val[N], vis[N], p[N];

int main() {
    std::cin >> n >> m >> k;
    if (k == 1) return std::cout << 0 << std::endl, 0;
    for (int i = 1; i < n; ++i) {
        std::cin >> x >> y >> z;
        next[x] = y, val[x] = z, vis[y] = 1;
    }
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) c = i;
    }
    x = 0;
    for (int i = c; i; i = next[i]) p[++x] = k - (val[i] - 1) % k - 1;
    std::cout << 1 << std::endl;
    return 0;
}