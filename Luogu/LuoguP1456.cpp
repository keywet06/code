#include <bits/stdc++.h>
const int N = 100005;
int n, m, x, y;
int f[N], val[N], ls[N], rs[N], dis[N];
inline int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (val[x] < val[y]) std::swap(x, y);
    rs[x] = merge(rs[x], y);
    if (dis[ls[x]] < dis[rs[x]]) std::swap(ls[x], rs[x]);
    dis[x] = dis[rs[x]] + 1;
    f[ls[x]] = f[rs[x]] = f[x] = x;
    return x;
}
inline int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }
int main() {
    dis[0] = -1;
    while (std::cin >> n) {
        for (int i = 1; i <= n; ++i) {
            std::cin >> val[i];
            ls[i] = rs[i] = dis[i] = 0;
            f[i] = i;
        }
        std::cin >> m;
        for (int i = 1; i <= m; ++i) {
            std::cin >> x >> y;
            x = find(x);
            y = find(y);
            if (x == y) {
                std::cout << -1 << std::endl;
                continue;
            }
            f[x] = merge(ls[x], rs[x]);
            f[y] = merge(ls[y], rs[y]);
            val[x] /= 2;
            val[y] /= 2;
            ls[x] = rs[x] = ls[y] = rs[y] = 0;
            merge(merge(x, f[x]), merge(y, f[y]));
            std::cout << val[find(x)] << std::endl;
        }
    }
    return 0;
}