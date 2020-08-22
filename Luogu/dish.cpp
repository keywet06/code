#include <bits/stdc++.h>
const int N = 10005;
int T, n, m, k, o;
int a[N], c[N];
inline int cmp(int x, int y) { return a[x] > a[y]; }
int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> T;
    while (T--) {
        std::cin >> n >> m >> k;
        for (int i = 1; i <= n; ++i) std::cin >> a[i], c[i] = i;
        std::sort(c + 1, c + n + 1, cmp);
        if (a[c[1]] < k) {
            std::cout << "-1" << std::endl;
        } else {
            for (int i = 1; i <= m; ++i) {
                std::cout << i << " " << k << std::endl;
            }
        }
    }
    return 0;
}