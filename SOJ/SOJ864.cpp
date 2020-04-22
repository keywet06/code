#include <bits/stdc++.h>
const int N = 200005;
int n, m, q, flag, x, y;
int f[N], t[N];
std::vector<int> out[N];
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> n >> m >> q;
    for (int i = 1; i < n; ++i) {
        std::cin >> x >> y;
        out[x].push_back(y);
        out[y].push_back(x);
    }
    for (int i = 1; i <= m; ++i) {
        std::cin >> x;
        f[x] = 1;
    }
    for (int i = 1; i <= q; ++i) {
        std::cin >> x;
        if (x == 1) {
            std::cin >> y;
            t[y] = 1;
        } else if (x == 2) {
            std::cin >> y;
            t[y] = 0;
        } else if (x == 3) {
            std::cin >> y;
            std::cout << (f[y] ? 'Y' : 'N') << "\n";
        } else {
            if (flag) {
                continue;
            }
            flag = 1;
            for (int i = 1; i <= n; ++i) {
                if (f[i] && !t[i]) {
                    flag = !flag && f[i];
                    continue;
                }
                for (auto it: out[i]) {
                    if (!t[it]) {
                        f[it] = 1;
                    }
                }
            }
        }
    }
    return 0;
}